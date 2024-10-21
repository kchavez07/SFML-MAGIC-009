#include "BaseApp.h"

/**
 * @brief Método principal que ejecuta la aplicación.
 *
 * Inicializa los recursos, mantiene el bucle principal mientras la ventana está abierta,
 * y al final libera los recursos.
 *
 * @return 0 si la ejecución fue exitosa.
 */
int BaseApp::run() {
    if (!initialize()) {
        ERROR("BaseApp", "run", "Initializes result on a false statement, check method validations");
    }
    while (m_window->isOpen()) {
        m_window->handleEvents();
        update();
        render();
    }

    cleanup();
    return 0;
}

/**
 * @brief Inicializa los actores, la ventana y otros recursos necesarios.
 *
 * @return true si la inicialización fue exitosa, false si hubo errores.
 */
bool BaseApp::initialize() {
    // Crear la ventana principal.
    m_window = new Window(800, 600, "Galvan Engine");
    if (!m_window) {
        ERROR("BaseApp", "initialize", "Error on window creation, var is null");
        return false;
    }

    // Crear el actor Track con forma de rectángulo.
    Track = EngineUtilities::MakeShared<Actor>("Track");
    if (!Track.isNull()) {
        Track->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);
        Track->getComponent<Transform>()->setPosition(sf::Vector2f(0.0f, 0.0f));

        // Corrección: Rotación debe ser un valor float, no un vector.
        Track->getComponent<Transform>()->setRotation(0.0f);

        Track->getComponent<Transform>()->setScale(sf::Vector2f(11.0f, 12.0f));

        // Cargar la textura del rectángulo.
        if (!texture.loadFromFile("Circuit.png")) {
            std::cout << "Error de carga de textura" << std::endl;
            return false;
        }
        Track->getComponent<ShapeFactory>()->getShape()->setTexture(&texture);
    }

    // Crear el actor Circle con forma de círculo.
    Circle = EngineUtilities::MakeShared<Actor>("Circle");
    if (!Circle.isNull()) {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
        Circle->getComponent<Transform>()->setPosition(sf::Vector2f(200.0f, 200.0f));

        // Corrección: Rotación debe ser un float.
        Circle->getComponent<Transform>()->setRotation(0.0f);

        Circle->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));
    }

    // Crear el actor Triangle con forma de triángulo.
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull()) {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
        Triangle->getComponent<Transform>()->setPosition(sf::Vector2f(200.0f, 200.0f));

        // Corrección: Rotación como un valor float.
        Triangle->getComponent<Transform>()->setRotation(0.0f);

        Triangle->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));
    }

    return true;
}

/**
 * @brief Actualiza la lógica del juego cada frame.
 */
void BaseApp::update() {
    // Actualiza la ventana.
    m_window->update();

    // Obtener la posición del ratón.
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    // Actualizar los actores.
    if (!Track.isNull()) {
        Track->update(m_window->deltaTime.asSeconds());
    }
    if (!Triangle.isNull()) {
        Triangle->update(m_window->deltaTime.asSeconds());
    }
    if (!Circle.isNull()) {
        Circle->update(m_window->deltaTime.asSeconds());

        // Obtener la posición actual del círculo.
        sf::Vector2f currentPosition = Circle->getComponent<Transform>()->getPosition();

        // Calcular la distancia entre el círculo y el ratón.
        float mouseDistance = std::sqrt(
            std::pow(mousePosF.x - currentPosition.x, 2) +
            std::pow(mousePosF.y - currentPosition.y, 2)
        );

        // Activar el seguimiento del ratón si está cerca.
        if (mouseDistance < 200.0f) {
            isFollowingMouse = true;

            // Movimiento suave hacia el ratón.
            sf::Vector2f newPos = currentPosition + (mousePosF - currentPosition) * m_window->deltaTime.asSeconds();
            Circle->getComponent<Transform>()->setPosition(newPos);
        }
        else {
            isFollowingMouse = false;
        }

        // Si no sigue al ratón, moverse entre los puntos predefinidos.
        if (!isFollowingMouse) {
            updateMovement(m_window->deltaTime.asSeconds(), Circle);
        }
    }
}

/**
 * @brief Renderiza los actores y la interfaz de ImGui.
 */
void BaseApp::render() {
    m_window->clear();

    if (!Track.isNull()) {
        Track->render(*m_window);
    }
    if (!Circle.isNull()) {
        Circle->render(*m_window);
    }
    if (!Triangle.isNull()) {
        Triangle->render(*m_window);
    }

    // Mostrar la interfaz de ImGui.
    ImGui::Begin("Hello, world!");
    ImGui::Text("This is a simple example.");
    ImGui::End();

    m_window->render();
    m_window->display();
}

/**
 * @brief Libera los recursos de la aplicación.
 */
void BaseApp::cleanup() {
    m_window->destroy();
    delete m_window;
}

/**
 * @brief Controla el movimiento del círculo entre puntos predefinidos.
 *
 * @param deltaTime Tiempo transcurrido desde el último frame.
 * @param circle Referencia al actor círculo.
 */
void BaseApp::updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle) {
    if (!circle || circle.isNull()) return;

    auto transform = circle->getComponent<Transform>();
    if (transform.isNull()) return;

    sf::Vector2f targetPos = waypoints[currentWaypoint];

    // Mover el círculo hacia el punto objetivo.
    transform->setPosition(targetPos);

    // Verificar si el círculo ha alcanzado el punto objetivo.
    sf::Vector2f currentPos = transform->getPosition();
    float distanceToTarget = std::sqrt(
        std::pow(targetPos.x - currentPos.x, 2) +
        std::pow(targetPos.y - currentPos.y, 2)
    );

    if (distanceToTarget < 10.0f) {
        currentWaypoint = (currentWaypoint + 1) % waypoints.size();
    }
}
