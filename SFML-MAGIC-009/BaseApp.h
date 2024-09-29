#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "ShapeFactory.h"
#include "Actor.h"
#include <SFML/Graphics.hpp>


class BaseApp
{
public:
	BaseApp() = default;
	~BaseApp() = default;

    //Funcion encargada de ejecutar la aplicacion en main
    int run();

    //Funcion de inicializacion
    bool initialize() {
        m_window = new Window(800, 600, "SFML-MAGIC-009");
        if (!m_window) {
            ERROR("BaseApp", "initialize", "Error on window creation, var is null");
            return false;
        }

        shape = new sf::CircleShape(10.0f);
        if (!shape) {
            ERROR("BaseApp", "initialize", "Error on shape creation, var is null");
            return false;
        }

        shape->setFillColor(sf::Color::Blue);
        shape->setPosition(200.0f, 200.0f);

        //Triangle Actor 
        Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
        if (!Triangle.isNull())
        {
            Triangle->getcomponents<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
        }

        return true;
    }

    //Funcion que se actualiza por frame
    void updapte();

    //Funcion de renderizado 
    void render();

    // Funcion de liberacion de recursos
    void clenaup();

private:
    Window* m_window;
    sf::CircleShape* shape;
    EngineUtilities::TSharedPointer<Actor> Triangle;
    //ShapeFactory m_shapeFactory;
    //sf::Shape* Triangulo;
};


