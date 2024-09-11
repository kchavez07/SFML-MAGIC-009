#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include <SFML/Graphics.hpp>

class BaseApp
{
public:
	BaseApp() = default;
	~BaseApp() = default;

    //Funcion encargada de ejecutar la aplicacion en main
    int run();

    //Funcion de inicializacion
    void initialize();

    //Funcion que se actualiza por frame
    void updapte();

    //Funcion de renderizado 
    void render();

    // Funcion de liberacion de recursos
    void clenaup();

private:
    Window* m_window;
    sf::CircleShape* shape;
};


