#pragma once
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

    //Funcion de manejo de datos
    void handleEvents();

    //Funcion que se actualiza por frame
    void updapte();

    //Funcion de renderizado 
    void render();

    // Funcion de liberacion de recursos
    void clenaup();

private:
	sf::RenderWindow* window;
	sf::CircleShape* shape;

};


