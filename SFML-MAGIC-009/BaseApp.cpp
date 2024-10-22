#include "BaseApp.h"

/**
 * @brief Método principal que ejecuta la aplicación.
 *
 * Este método mantiene la aplicación en un bucle continuo, manejando eventos,
 * actualizando la lógica del juego y renderizando los actores hasta que se cierre la ventana.
 *
 * @return int Código de salida (0 si la ejecución fue exitosa).
 */
int BaseApp::run() {
    if (!initialize()) {
        ERROR("BaseApp", "run", "Initialization failed. Check method validations.");
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
 * @brief Inicializa los recursos necesarios, como actores y texturas.
 *
 * Se encarga de crear la ventana, cargar las texturas del circuito y los personajes,
 * así como inicializar los actores con las transformaciones y texturas correspondientes.
 *
 * @return true Si la inicialización fue exitosa, false si ocurrió un error.
 */
bool BaseApp::initialize() {
    // Crear la ventana principal.
    m_window = new Window(800, 600, "SFML-MAGIC-009");
    if (!m_window) {
        ERROR("BaseApp", "initialize", "Error al crear la ventana.");
        return false;
    }

    // Cargar la textura del circuito.
    if (!texture.loadFromFile("C:/Users/kevin/OneDrive/Documentos/GitHub/SFML-MAGIC-009/bin/MarioKart sprite-png/Circuit.png")) {
        std::cout << "Error al cargar la textura del circuito" << std::endl;
        return false;
    }

    // Crear y configurar el Track (pista).
    Track = EngineUtilities::MakeShared<Actor>("Track");
    if (!Track.isNull()) {
        auto trackTransform = Track->getComponent<Transform>();
        Track->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);
        trackTransform->setPosition(sf::Vector2f(0.0f, 0.0f));
        trackTransform->setRotation(0.0f);
        trackTransform->setScale(sf::Vector2f(11.0f, 12.0f));
        Track->getComponent<ShapeFactory>()->getShape()->setTexture(&texture);
    }

    // Función lambda para cargar y asignar texturas a personajes.
    auto loadCharacter = [this](sf::Texture& texture, const std::string& path, const std::string& name) {
        if (!texture.loadFromFile(path)) {
            std::cout << "Error al cargar la textura de " << name << std::endl;
            return false;
        }
        return true;
        };

    // Lista de personajes y sus rutas de textura.
    std::vector<std::pair<sf::Texture*, std::string>> characters = {
        {&Mario, "tile000.png"}, {&Luigi, "tile001.png"},
        {&Peach, "tile002.png"}, {&Toad, "tile003.png"},
        {&Yoshi, "tile004.png"}, {&DonkeyKong, "tile005.png"},
        {&Wario, "tile006.png"}
    };

    // Cargar texturas de los personajes.
    for (const auto& [texture, path] : characters) {
        if (!loadCharacter(*texture, "C:/Users/kevin/OneDrive/Documentos/GitHub/SFML-MAGIC-009/bin/MarioKart sprite-png/" + path, path)) {
            return false;
        }
    }

    // Crear el actor Circle (ejemplo con Mario).
    Circle = EngineUtilities::MakeShared<Actor>("Circle");
    if (!Circle.isNull()) {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
        auto circleTransform = Circle->getComponent<Transform>();
        circleTransform->setPosition(sf::Vector2f(200.0f, 200.0f));
        circleTransform->setRotation(0.0f);
        circleTransform->setScale(sf::Vector2f(1.0f, 1.0f));
        Circle->getComponent<ShapeFactory>()->getShape()->setTexture(&Mario);
    }

    return true;
}

/**
 * @brief Actualiza la lógica del juego cada frame.
 *
 * Este método maneja la actualización de los actores, la posición del ratón y el movimiento del círculo.
 */
void BaseApp::update() {
    m_window->update();

    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    if (!Track.isNull()) Track->update(m_window->deltaTime.asSeconds());
    if (!Triangle.isNull()) Triangle->update(m_window->deltaTime.asSeconds());

    if (!Circle.isNull()) {
        Circle->update(m_window->deltaTime.asSeconds());

        sf::Vector2f currentPosition = Circle->getComponent<Transform>()->getPosition();
        float mouseDistance = std::sqrt(
            std::pow(mousePosF.x - currentPosition.x, 2) + std::pow(mousePosF.y - currentPosition.y, 2)
        );

        if (mouseDistance < 100.0f) {
            isFollowingMouse = true;
            sf::Vector2f newPos = currentPosition + (mousePosF - currentPosition) * m_window->deltaTime.asSeconds();
            Circle->getComponent<Transform>()->setPosition(newPos);
        }
        else {
            isFollowingMouse = false;
            updateMovement(m_window->deltaTime.asSeconds(), Circle);
        }
    }
}

/**
 * @brief Renderiza los actores y la interfaz gráfica de ImGui.
 */
void BaseApp::render() {
    m_window->clear();

    if (!Track.isNull()) Track->render(*m_window);
    if (!Circle.isNull()) Circle->render(*m_window);
    if (!Triangle.isNull()) Triangle->render(*m_window);

    ImGui::Begin("Hello, world!");
    ImGui::Text("This is a simple example.");
    ImGui::End();

    m_window->render();
    m_window->display();
}

/**
 * @brief Libera los recursos utilizados por la aplicación.
 *
 * Este método destruye la ventana y libera la memoria asignada.
 */
void BaseApp::cleanup() {
    m_window->destroy();
    delete m_window;
}

/**
 * @brief Controla el movimiento del círculo entre puntos predefinidos.
 *
 * Si el círculo no sigue al ratón, se mueve automáticamente entre waypoints.
 *
 * @param deltaTime Tiempo transcurrido desde el último frame.
 * @param circle Actor del círculo a mover.
 */
void BaseApp::updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle) {
    if (circle.isNull()) return;

    auto transform = circle->getComponent<Transform>();
    sf::Vector2f currentPos = transform->getPosition();
    sf::Vector2f targetPos = waypoints[currentWaypoint];

    sf::Vector2f direction = targetPos - currentPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0.0f) direction /= distance;

    float speed = 150.0f;  // Velocidad del círculo.
    sf::Vector2f newPos = currentPos + direction * speed * deltaTime;

    if (distance < 10.0f) {
        currentWaypoint = (currentWaypoint + 1) % waypoints.size();
    }
    else {
        transform->setPosition(newPos);
    }
}
