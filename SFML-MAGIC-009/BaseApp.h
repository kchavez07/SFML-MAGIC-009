#pragma once

#include "Prerequisites.h"
#include "Window.h"
#include "Actor.h"

// Clase principal de la aplicación
class BaseApp
{
public:
    BaseApp() = default;  // Constructor por defecto
    ~BaseApp() = default;  // Destructor por defecto

    // Función encargada de ejecutar la aplicación en main
    int run();

    // Función de inicialización
    bool initialize();

    // Función que se actualiza por frame
    void update(); 

    // Función de renderizado
    void render();

    // Función de liberación de recursos
    void cleanup();

private:
    Window* m_window;  // Ventana principal de la aplicación
    EngineUtilities::TSharedPointer<Actor> Triangle; 
    EngineUtilities::TSharedPointer<Actor> Circle;

    sf::Clock Clock;  // Reloj para medir el tiempo entre frames
    sf::Time deltaTime;  // Tiempo delta calculado entre cada frame
};

