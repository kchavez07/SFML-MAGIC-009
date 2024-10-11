#include "Actor.h"
#include "BaseApp.h"

/*
 * BaseApp.cpp
 * Este archivo contiene la lógica principal de la aplicación que gestiona la ventana, actualiza los actores (círculo y triángulo),
 * y maneja el comportamiento del círculo azul. El círculo se mueve entre cuatro puntos en la pantalla
 * y también sigue al ratón si está lo suficientemente cerca.
 */

 // Definir los cuatro puntos de referencia en la esquina superior derecha de la ventana.
 // El círculo azul se moverá automáticamente entre estos puntos cuando no esté siguiendo al ratón.
std::vector<sf::Vector2f> points = {
    sf::Vector2f(600.0f, 100.0f),
    sf::Vector2f(700.0f, 100.0f),
    sf::Vector2f(700.0f, 200.0f),
    sf::Vector2f(600.0f, 200.0f)
};

int currentTarget = 0;  // Índice que lleva un seguimiento del punto objetivo actual.
float actorSpeed = 50.0f;  // Velocidad del círculo ajustada para moverse suavemente entre puntos.
float range = 5.0f;  // Rango para considerar que el círculo ha llegado al objetivo.
bool isFollowingMouse = false;  // Variable que indica si el círculo está siguiendo al ratón.

// Función principal que ejecuta la lógica de la aplicación.
// Se encarga de inicializar la ventana, el bucle de juego principal y la limpieza de recursos.
int BaseApp::run()
{
    if (!initialize())  // Comprobar si la inicialización es exitosa.
    {
        ERROR("BaseApp", "run", "Error al inicializar, comprueba las validaciones del método.");
    }

    // Bucle principal del juego, que se ejecuta mientras la ventana esté abierta.
    while (m_window->isOpen())
    {
        m_window->handleEvents();  // Gestionar los eventos de la ventana (cerrar, minimizar, etc.).

        deltaTime = Clock.restart();  // Calcular el tiempo transcurrido desde el último frame.

        update();  // Actualizar la lógica del juego.
        render();  // Dibujar los objetos en la pantalla.
    }

    cleanup();  // Liberar recursos y cerrar la aplicación.

    return 0;
}

// Inicialización de la ventana y creación de los actores (círculo y triángulo).
bool BaseApp::initialize()
{
    // Crear una ventana con las dimensiones y el título especificado.
    m_window = new Window(800, 600, "SFML-MAGIC-009");
    if (m_window == nullptr)  // Comprobar si la ventana se creó correctamente.
    {
        ERROR("BaseApp", "initialize", "Error al crear la ventana, el puntero es nulo.");
        return false;
    }

    // Crear el actor del círculo y configurarlo con sus propiedades iniciales.
    Circle = EngineUtilities::MakeShared<Actor>("Circle");
    if (!Circle.isNull())
    {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);  // Crear la forma de círculo.
        Circle->getComponent<ShapeFactory>()->getShape()->setFillColor(sf::Color::Blue);  // Color azul para distinguirlo.
    }

    // Establecer la posición, rotación y escala inicial del círculo a través del componente `Transform`.
    Circle->getComponent<Transform>()->setPosition(sf::Vector2f(600.0f, 100.0f));
    Circle->getComponent<Transform>()->setRotation(0.0f);
    Circle->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));

    // Crear el actor del triángulo y posicionarlo en la esquina superior izquierda.
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull())
    {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);  // Crear la forma de triángulo.
        Triangle->getComponent<ShapeFactory>()->getShape()->setFillColor(sf::Color::Yellow);  // Color amarillo para el triángulo.
    }

    // Establecer la posición, rotación y escala inicial del triángulo a través del componente `Transform`.
    Triangle->getComponent<Transform>()->setPosition(sf::Vector2f(0.0f, 0.0f));
    Triangle->getComponent<Transform>()->setRotation(0.0f);
    Triangle->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));

    return true;
}

// Función de actualización que se ejecuta en cada frame.
// Controla el movimiento del círculo y verifica si sigue al ratón o se mueve entre los puntos predefinidos.
void BaseApp::update()
{
    // Obtener la posición actual del ratón dentro de la ventana.
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    if (!Circle.isNull())  // Comprobar si el actor del círculo es válido.
    {
        Circle->update(deltaTime.asSeconds());
        Triangle->update(deltaTime.asSeconds());

        // Obtener la posición actual del círculo desde el componente `Transform`.
        sf::Vector2f currentPosition = Circle->getComponent<Transform>()->getPosition();

        // Calcular la distancia entre el círculo y la posición del ratón.
        float mouseDistance = std::sqrt((mousePosF.x - currentPosition.x) * (mousePosF.x - currentPosition.x) +
            (mousePosF.y - currentPosition.y) * (mousePosF.y - currentPosition.y));

        // Si el ratón está lo suficientemente cerca, activar el seguimiento del ratón.
        if (mouseDistance < 200.0f)
        {
            isFollowingMouse = true;

            // Interpolación para suavizar el movimiento hacia el ratón.
            sf::Vector2f newPos = currentPosition + (mousePosF - currentPosition) * deltaTime.asSeconds();
            Circle->getComponent<Transform>()->setPosition(newPos);  // Actualizamos la posición suavemente.
        }
        else
        {
            isFollowingMouse = false;  // Dejar de seguir al ratón si está muy lejos.
        }

        // Si no está siguiendo al ratón, moverse automáticamente entre los puntos predefinidos.
        if (!isFollowingMouse)
        {
            // Calcular la dirección hacia el punto objetivo actual.
            sf::Vector2f direction = points[currentTarget] - currentPosition;

            // Calcular la distancia al punto objetivo.
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            // Si la distancia es menor al rango especificado, pasar al siguiente punto.
            if (distance < range)
            {
                currentTarget = (currentTarget + 1) % points.size();  // Avanzar al siguiente punto.
            }

            // Normalizar la dirección
            if (distance > 0.0f)
            {
                direction /= distance;
            }

            // Mover el círculo hacia el punto objetivo actual utilizando el componente `Transform`.
            sf::Vector2f newPos = currentPosition + direction * actorSpeed * deltaTime.asSeconds();
            Circle->getComponent<Transform>()->setPosition(newPos);
        }
    }
}

// Función de renderizado que dibuja los actores en la pantalla.
void BaseApp::render()
{
    m_window->clear();  // Limpiar la pantalla antes de dibujar.

    // Dibujar ambos actores en la ventana.
    Circle->render(*m_window);  // Dibujar el círculo.
    Triangle->render(*m_window);  // Dibujar el triángulo.

    m_window->display();  // Mostrar en pantalla el contenido actual de la ventana.
}

// Función para liberar recursos al final de la ejecución de la aplicación.
void BaseApp::cleanup()
{
    // Liberar la memoria asignada a la ventana y al círculo.
    m_window->destroy();  // Destruir la ventana.
    delete m_window;
}
