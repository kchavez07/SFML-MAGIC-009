#include "Actor.h"
#include "BaseApp.h"

// Definir los cuatro puntos de referencia en la esquina superior derecha de la ventana.
// El círculo azul se moverá automáticamente entre estos puntos cuando no esté siguiendo al ratón.
std::vector<sf::Vector2f> points = {
    sf::Vector2f(600.0f, 100.0f),
    sf::Vector2f(700.0f, 100.0f),
    sf::Vector2f(700.0f, 200.0f),
    sf::Vector2f(600.0f, 200.0f)
};

int currentTarget = 0;  // Índice que lleva un seguimiento del punto objetivo actual.
float actorSpeed = 100.0f;  // Velocidad del círculo al moverse entre puntos.
float range = 5.0f;  // Rango para considerar que el círculo ha llegado al objetivo.

bool isFollowingMouse = false;  // Variable que indica si el círculo está siguiendo al ratón.

int BaseApp::run()
{
    if (!initialize())  // Comprobar si la inicialización es exitosa.
    {
        ERROR("BaseApp", "run", "Initializes result on a false statement, check method validations.");
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

bool BaseApp::initialize()
{
    // Crear una ventana con las dimensiones y el título especificado.
    m_window = new Window(800, 600, "SFML-MAGIC-009");
    if (m_window == nullptr)  // Comprobar si la ventana se creó correctamente.
    {
        ERROR("BaseApp", "initialize", "Error on window creation, var is null");
        return false;
    }

    // Crear el actor del círculo y configurarlo con sus propiedades iniciales.
    Circle = EngineUtilities::MakeShared<Actor>("Circle");
    if (!Circle.isNull())
    {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);  // Crear la forma de círculo.
        Circle->getComponent<ShapeFactory>()->setPosition(600.0f, 100.0f);  // Establecer la posición inicial en el primer punto.
        Circle->getComponent<ShapeFactory>()->getShape()->setFillColor(sf::Color::Blue);  // Color azul para distinguirlo.
    }

    // Crear el actor del triángulo y posicionarlo en la esquina superior izquierda.
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull())
    {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);  // Crear la forma de triángulo.
        Triangle->getComponent<ShapeFactory>()->setPosition(0.0f, 0.0f);  // Posición exacta en la esquina superior izquierda.
        Triangle->getComponent<ShapeFactory>()->getShape()->setFillColor(sf::Color::White);  // Color blanco para el triángulo.
    }

    return true;
}

void BaseApp::update()
{
    // Obtener la posición actual del ratón dentro de la ventana.
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    if (!Circle.isNull())  // Comprobar si el actor del círculo es válido.
    {
        // Obtener la posición actual del círculo.
        sf::Vector2f currentPosition = Circle->getComponent<ShapeFactory>()->getShape()->getPosition();

        // Calcular la distancia entre el círculo y la posición del ratón.
        float mouseDistance = std::sqrt((mousePosF.x - currentPosition.x) * (mousePosF.x - currentPosition.x) +
            (mousePosF.y - currentPosition.y) * (mousePosF.y - currentPosition.y));

        // Si el ratón está lo suficientemente cerca, activar el seguimiento del ratón.
        if (mouseDistance < 200.0f)
        {
            isFollowingMouse = true;
            Circle->getComponent<ShapeFactory>()->Seek(mousePosF, 200.0f, deltaTime.asSeconds(), 10.0f);
        }
        else
        {
            isFollowingMouse = false;  // Dejar de seguir el ratón si está muy lejos.
        }

        // Si no está siguiendo el ratón, moverse automáticamente entre los puntos predefinidos.
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

            // Mover el círculo hacia el punto objetivo actual.
            Circle->getComponent<ShapeFactory>()->Seek(points[currentTarget], actorSpeed, deltaTime.asSeconds(), range);
        }
    }
}

void BaseApp::render()
{
    m_window->clear();  // Limpiar la pantalla antes de dibujar.

    // Dibujar ambos actores en la ventana.
    Circle->render(*m_window);  // Dibujar el círculo.
    Triangle->render(*m_window);  // Dibujar el triángulo.

    m_window->display();  // Mostrar en pantalla el contenido actual de la ventana.
}

void BaseApp::cleanup()
{
    // Liberar la memoria asignada a la ventana y al círculo.
    m_window->destroy();  // Destruir la ventana.
    delete m_window;
}
