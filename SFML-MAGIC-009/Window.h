#pragma once
#include "Prerequisites.h"

class Window
{
public:
	Window() = default;
	Window(int width, int height, const std::string& title);
	~Window();

	//Funcion de manejo de datos
	void handleEvents();

	// Funcion que limpia el contenido de la ventana con el color prederterminado 
	void clear();

	// Funcion que muestra el contenido de la ventana en la pantalla 
	void display();

	//Funcion que verifica si la ventana sigue abierta 
	// @return true si la ventana esta abierta, flase en caso contrario 
	bool isOpen() const;

	//Funcion que dibuja un obejto que puede ser dibujado en la ventana
	//@param drawable refrencia a un objeto SFML que puede ser dibujado 
	void draw(const sf::Drawable& drawable);

	//Funcion que obtiene un objeto interno SFML RenderWiwdow
	//@return un puntero al objeto interno SFML RendeWindow
	sf::RenderWindow* getWindow();
	
	//Funcion de inicializacion
	void init();

	//Funcion que se actualiza por frame
	void updapte();

	//Funcion de renderizado 
	void render();

	void destroy();

private:
	sf::RenderWindow* m_window;
};

