#include "BaseApp.h"

int BaseApp::run()
{
    initialize();
    while (m_window->isOpen())
    {
        m_window->handleEvents();
        updapte();
        render();
    }
    clenaup();

    return 0;
}

void BaseApp::initialize(){
    m_window = new Window(800, 600, "SFML-MAGIC-009");
    shape = new sf::CircleShape(100.0f);
    shape->setFillColor(sf::Color::Green);
}

void BaseApp::updapte(){
}

void BaseApp::render(){
    m_window->getWindow();
    m_window->draw(*shape);
    m_window->display();
}

void BaseApp::clenaup()
{
    m_window->destroy();
    delete m_window;
    delete shape;
}
