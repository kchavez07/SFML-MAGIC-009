#include "Actor.h"
#include "BaseApp.h"

/*
 * BaseApp.cpp
 * Este archivo contiene la l�gica principal de la aplicaci�n que gestiona la ventana, actualiza los actores (c�rculo y tri�ngulo),
 * y maneja el comportamiento del c�rculo azul. El c�rculo se mueve entre cuatro puntos en la pantalla
 * y tambi�n sigue al rat�n si est� lo suficientemente cerca.
 */

 // Definir los cuatro puntos de referencia en la esquina superior derecha de la ventana.
 // El c�rculo azul se mover� autom�ticamente entre estos puntos cuando no est� siguiendo al rat�n.
std::vector<sf::Vector2f> points = {
    sf::Vector2f(600.0f, 100.0f),
    sf::Vector2f(700.0f, 100.0f),
    sf::Vector2f(700.0f, 200.0f),
    sf::Vector2f(600.0f, 200.0f)
};

int currentTarget = 0;  // �ndice que lleva un seguimiento del punto objetivo actual.
float actorSpeed = 50.0f;  // Velocidad del c�rculo ajustada para moverse suavemente entre puntos.
float range = 5.0f;  // Rango para considerar que el c�rculo ha llegado al objetivo.
bool isFollowingMouse = false;  // Variable que indica si el c�rculo est� siguiendo al rat�n.

// Funci�n principal que ejecuta la l�gica de la aplicaci�n.
// Se encarga de inicializar la ventana, el bucle de juego principal y la limpieza de recursos.
int BaseApp::run()
{
    if (!initialize())  // Comprobar si la inicializaci�n es exitosa.
    {
        ERROR("BaseApp", "run", "Error al inicializar, comprueba las validaciones del m�todo.");
    }

    // Bucle principal del juego, que se ejecuta mientras la ventana est� abierta.
    while (m_window->isOpen())
    {
        m_window->handleEvents();  // Gestionar los eventos de la ventana (cerrar, minimizar, etc.).

        deltaTime = Clock.restart();  // Calcular el tiempo transcurrido desde el �ltimo frame.

        update();  // Actualizar la l�gica del juego.
        render();  // Dibujar los objetos en la pantalla.
    }

    cleanup();  // Liberar recursos y cerrar la aplicaci�n.

    return 0;
}

// Inicializaci�n de la ventana y creaci�n de los actores (c�rculo y tri�ngulo).
bool BaseApp::initialize()
{
    // Crear una ventana con las dimensiones y el t�tulo especificado.
    m_window = new Window(800, 600, "SFML-MAGIC-009");
    if (m_window == nullptr)  // Comprobar si la ventana se cre� correctamente.
    {
        ERROR("BaseApp", "initialize", "Error al crear la ventana, el puntero es nulo.");
        return false;
    }

    // Crear el actor del c�rculo y configurarlo con sus propiedades iniciales.
    Circle = EngineUtilities::MakeShared<Actor>("Circle");
    if (!Circle.isNull())
    {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);  // Crear la forma de c�rculo.
        Circle->getComponent<ShapeFactory>()->getShape()->setFillColor(sf::Color::Blue);  // Color azul para distinguirlo.
    }

    // Establecer la posici�n, rotaci�n y escala inicial del c�rculo a trav�s del componente `Transform`.
    Circle->getComponent<Transform>()->setPosition(sf::Vector2f(600.0f, 100.0f));
    Circle->getComponent<Transform>()->setRotation(0.0f);
    Circle->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));

    // Crear el actor del tri�ngulo y posicionarlo en la esquina superior izquierda.
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull())
    {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);  // Crear la forma de tri�ngulo.
        Triangle->getComponent<ShapeFactory>()->getShape()->setFillColor(sf::Color::Yellow);  // Color amarillo para el tri�ngulo.
    }

    // Establecer la posici�n, rotaci�n y escala inicial del tri�ngulo a trav�s del componente `Transform`.
    Triangle->getComponent<Transform>()->setPosition(sf::Vector2f(0.0f, 0.0f));
    Triangle->getComponent<Transform>()->setRotation(0.0f);
    Triangle->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));

    return true;
}

// Funci�n de actualizaci�n que se ejecuta en cada frame.
// Controla el movimiento del c�rculo y verifica si sigue al rat�n o se mueve entre los puntos predefinidos.
void BaseApp::update()
{
    // Obtener la posici�n actual del rat�n dentro de la ventana.
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    if (!Circle.isNull())  // Comprobar si el actor del c�rculo es v�lido.
    {
        Circle->update(deltaTime.asSeconds());
        Triangle->update(deltaTime.asSeconds());

        // Obtener la posici�n actual del c�rculo desde el componente `Transform`.
        sf::Vector2f currentPosition = Circle->getComponent<Transform>()->getPosition();

        // Calcular la distancia entre el c�rculo y la posici�n del rat�n.
        float mouseDistance = std::sqrt((mousePosF.x - currentPosition.x) * (mousePosF.x - currentPosition.x) +
            (mousePosF.y - currentPosition.y) * (mousePosF.y - currentPosition.y));

        // Si el rat�n est� lo suficientemente cerca, activar el seguimiento del rat�n.
        if (mouseDistance < 200.0f)
        {
            isFollowingMouse = true;

            // Interpolaci�n para suavizar el movimiento hacia el rat�n.
            sf::Vector2f newPos = currentPosition + (mousePosF - currentPosition) * deltaTime.asSeconds();
            Circle->getComponent<Transform>()->setPosition(newPos);  // Actualizamos la posici�n suavemente.
        }
        else
        {
            isFollowingMouse = false;  // Dejar de seguir al rat�n si est� muy lejos.
        }

        // Si no est� siguiendo al rat�n, moverse autom�ticamente entre los puntos predefinidos.
        if (!isFollowingMouse)
        {
            // Calcular la direcci�n hacia el punto objetivo actual.
            sf::Vector2f direction = points[currentTarget] - currentPosition;

            // Calcular la distancia al punto objetivo.
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            // Si la distancia es menor al rango especificado, pasar al siguiente punto.
            if (distance < range)
            {
                currentTarget = (currentTarget + 1) % points.size();  // Avanzar al siguiente punto.
            }

            // Normalizar la direcci�n
            if (distance > 0.0f)
            {
                direction /= distance;
            }

            // Mover el c�rculo hacia el punto objetivo actual utilizando el componente `Transform`.
            sf::Vector2f newPos = currentPosition + direction * actorSpeed * deltaTime.asSeconds();
            Circle->getComponent<Transform>()->setPosition(newPos);
        }
    }
}

// Funci�n de renderizado que dibuja los actores en la pantalla.
void BaseApp::render()
{
    m_window->clear();  // Limpiar la pantalla antes de dibujar.

    // Dibujar ambos actores en la ventana.
    Circle->render(*m_window);  // Dibujar el c�rculo.
    Triangle->render(*m_window);  // Dibujar el tri�ngulo.

    m_window->display();  // Mostrar en pantalla el contenido actual de la ventana.
}

// Funci�n para liberar recursos al final de la ejecuci�n de la aplicaci�n.
void BaseApp::cleanup()
{
    // Liberar la memoria asignada a la ventana y al c�rculo.
    m_window->destroy();  // Destruir la ventana.
    delete m_window;
}
