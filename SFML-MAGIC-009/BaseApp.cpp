#include "Actor.h"
#include "BaseApp.h"

int BaseApp::run()
{
    if (!initialize())
    {
        ERROR("BaseApp", "run", "Initializes result on a false statement, check method validations.");
    }

    while (m_window->isOpen())
    {
        m_window->handleEvents();  // Manejar eventos de la ventana

        // Parte exacta del c�digo seg�n la captura:
        deltaTime = Clock.restart();  // Calcular deltaTime usando Clock.restart()

        update();  // Llamar a `update` (sin par�metros si es como la versi�n que mostraste)
        render();  // Renderizar los objetos en la pantalla
    }

    cleanup();

    return 0;
}


bool BaseApp::initialize()
{
    m_window = new Window(800, 600, "SFML-MAGIC-009");
    if (m_window == nullptr)
    {
        ERROR("BaseApp", "initialize", "Error on window creation, var is null");
        return false;
    }

    // C�rculo Actor
    Circle = EngineUtilities::MakeShared<Actor>("Circle");
    if (!Circle.isNull())
    {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
        Circle->getComponent<ShapeFactory>()->setPosition(200.0f, 200.0f);
        Circle->getComponent<ShapeFactory>()->getShape()->setFillColor(sf::Color::Blue);
    }

    // Tri�ngulo Actor
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull())
    {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
    }

    return true;
}

void BaseApp::update()
{
    // Mouse Position
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    if (!Circle.isNull())
    {
        Circle->getComponent<ShapeFactory>()->Seek(mousePosF, 200.0f, deltaTime.asSeconds(), 10.0f); 
    }
}

void BaseApp::render()
{
    m_window->clear();  // Limpiar la pantalla
    Circle->render(*m_window);  // Renderizar el c�rculo
    Triangle->render(*m_window);  // Renderizar el tri�ngulo
    m_window->display();  // Mostrar el contenido de la ventana
}


void BaseApp::cleanup()
{
    m_window->destroy();
    delete m_window;
    
}
