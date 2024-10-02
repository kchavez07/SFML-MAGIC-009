#include "Actor.h"
#include "BaseApp.h"

// Definir los cuatro puntos de referencia en la esquina superior derecha de la ventana.
// El c�rculo azul se mover� autom�ticamente entre estos puntos cuando no est� siguiendo al rat�n.
std::vector<sf::Vector2f> points = {
    sf::Vector2f(600.0f, 100.0f),
    sf::Vector2f(700.0f, 100.0f),
    sf::Vector2f(700.0f, 200.0f),
    sf::Vector2f(600.0f, 200.0f)
};

int currentTarget = 0;  // �ndice que lleva un seguimiento del punto objetivo actual.
float actorSpeed = 100.0f;  // Velocidad del c�rculo al moverse entre puntos.
float range = 5.0f;  // Rango para considerar que el c�rculo ha llegado al objetivo.

bool isFollowingMouse = false;  // Variable que indica si el c�rculo est� siguiendo al rat�n.

int BaseApp::run()
{
    if (!initialize())  // Comprobar si la inicializaci�n es exitosa.
    {
        ERROR("BaseApp", "run", "Initializes result on a false statement, check method validations.");
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

bool BaseApp::initialize()
{
    // Crear una ventana con las dimensiones y el t�tulo especificado.
    m_window = new Window(800, 600, "SFML-MAGIC-009");
    if (m_window == nullptr)  // Comprobar si la ventana se cre� correctamente.
    {
        ERROR("BaseApp", "initialize", "Error on window creation, var is null");
        return false;
    }

    // Crear el actor del c�rculo y configurarlo con sus propiedades iniciales.
    Circle = EngineUtilities::MakeShared<Actor>("Circle");
    if (!Circle.isNull())
    {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);  // Crear la forma de c�rculo.
        Circle->getComponent<ShapeFactory>()->setPosition(600.0f, 100.0f);  // Establecer la posici�n inicial en el primer punto.
        Circle->getComponent<ShapeFactory>()->getShape()->setFillColor(sf::Color::Blue);  // Color azul para distinguirlo.
    }

    // Crear el actor del tri�ngulo y posicionarlo en la esquina superior izquierda.
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull())
    {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);  // Crear la forma de tri�ngulo.
        Triangle->getComponent<ShapeFactory>()->setPosition(0.0f, 0.0f);  // Posici�n exacta en la esquina superior izquierda.
        Triangle->getComponent<ShapeFactory>()->getShape()->setFillColor(sf::Color::White);  // Color blanco para el tri�ngulo.
    }

    return true;
}

void BaseApp::update()
{
    // Obtener la posici�n actual del rat�n dentro de la ventana.
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    if (!Circle.isNull())  // Comprobar si el actor del c�rculo es v�lido.
    {
        // Obtener la posici�n actual del c�rculo.
        sf::Vector2f currentPosition = Circle->getComponent<ShapeFactory>()->getShape()->getPosition();

        // Calcular la distancia entre el c�rculo y la posici�n del rat�n.
        float mouseDistance = std::sqrt((mousePosF.x - currentPosition.x) * (mousePosF.x - currentPosition.x) +
            (mousePosF.y - currentPosition.y) * (mousePosF.y - currentPosition.y));

        // Si el rat�n est� lo suficientemente cerca, activar el seguimiento del rat�n.
        if (mouseDistance < 200.0f)
        {
            isFollowingMouse = true;
            Circle->getComponent<ShapeFactory>()->Seek(mousePosF, 200.0f, deltaTime.asSeconds(), 10.0f);
        }
        else
        {
            isFollowingMouse = false;  // Dejar de seguir el rat�n si est� muy lejos.
        }

        // Si no est� siguiendo el rat�n, moverse autom�ticamente entre los puntos predefinidos.
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

            // Mover el c�rculo hacia el punto objetivo actual.
            Circle->getComponent<ShapeFactory>()->Seek(points[currentTarget], actorSpeed, deltaTime.asSeconds(), range);
        }
    }
}

void BaseApp::render()
{
    m_window->clear();  // Limpiar la pantalla antes de dibujar.

    // Dibujar ambos actores en la ventana.
    Circle->render(*m_window);  // Dibujar el c�rculo.
    Triangle->render(*m_window);  // Dibujar el tri�ngulo.

    m_window->display();  // Mostrar en pantalla el contenido actual de la ventana.
}

void BaseApp::cleanup()
{
    // Liberar la memoria asignada a la ventana y al c�rculo.
    m_window->destroy();  // Destruir la ventana.
    delete m_window;
}
