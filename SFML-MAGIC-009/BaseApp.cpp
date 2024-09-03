#include "BaseApp.h"

int BaseApp::run()
{
    initialize();
    while (window->isOpen())
    {
        handleEvents();
        updapte();
        render();
    }
    clenaup();

    return 0;
}

void BaseApp::initialize(){
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML-MAGIC-009");
    shape = new sf::CircleShape(100.0f);
    shape->setFillColor(sf::Color::Green);
}

void BaseApp::handleEvents(){
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void BaseApp::updapte(){
}

void BaseApp::render(){
    window->clear();
    window->draw(*shape);
    window->display();
}

void BaseApp::clenaup(){
    delete window;
    delete shape;
}
