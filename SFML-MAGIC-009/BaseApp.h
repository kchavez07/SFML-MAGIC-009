#pragma once

#include "Prerequisites.h"
#include "Window.h"
#include "Actor.h"

// Clase principal de la aplicaci�n
class BaseApp
{
public:
    BaseApp() = default;  // Constructor por defecto
    ~BaseApp() = default;  // Destructor por defecto

    // Funci�n encargada de ejecutar la aplicaci�n en main
    int run();

    // Funci�n de inicializaci�n
    bool initialize();

    // Funci�n que se actualiza por frame
    void update(); 

    // Funci�n de renderizado
    void render();

    // Funci�n de liberaci�n de recursos
    void cleanup();

private:
    Window* m_window;  // Ventana principal de la aplicaci�n
    EngineUtilities::TSharedPointer<Actor> Triangle; 
    EngineUtilities::TSharedPointer<Actor> Circle;

    sf::Clock Clock;  // Reloj para medir el tiempo entre frames
    sf::Time deltaTime;  // Tiempo delta calculado entre cada frame
};

