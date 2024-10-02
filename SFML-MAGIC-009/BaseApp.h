#pragma once

#include "Prerequisites.h"
#include "Window.h"
#include "Actor.h"

// @class BaseApp
// @brief Clase principal que controla el flujo de la aplicaci�n.
// Esta clase se encarga de gestionar la ventana, los actores (como el c�rculo y el tri�ngulo),
// y las funciones de renderizado, actualizaci�n y liberaci�n de recursos.
class BaseApp
{
public:
    BaseApp() = default;  // Constructor por defecto.
    ~BaseApp() = default;  // Destructor por defecto.

    // @brief Funci�n principal de ejecuci�n de la aplicaci�n.
    // Se encarga de llamar a la inicializaci�n, el bucle de actualizaci�n y renderizado,
    // y finalmente liberar recursos cuando la aplicaci�n finaliza.
    // @return C�digo de salida (normalmente 0 si todo sale bien).
    int run();

    // @brief Funci�n de inicializaci�n.
    // Aqu� se crean la ventana principal y los actores (como el c�rculo y el tri�ngulo).
    // Tambi�n se define su posici�n y apariencia inicial.
    // @return true si la inicializaci�n fue exitosa, false si hubo alg�n error.
    bool initialize();

    // @brief Funci�n de actualizaci�n que se llama en cada frame.
    // Aqu� se implementa la l�gica que cambia cada vez que avanza el tiempo (como el movimiento).
    // Realiza el seguimiento del rat�n y el movimiento entre los puntos predeterminados.
    void update();

    // @brief Funci�n de renderizado que dibuja los elementos en la pantalla.
    // Se llama en cada frame despu�s de la actualizaci�n para mostrar los actores.
    void render();

    // @brief Funci�n de limpieza que libera los recursos y destruye la ventana.
    // Es la �ltima funci�n que se ejecuta cuando la aplicaci�n est� cerrando.
    void cleanup();

private:
    Window* m_window;  // Puntero a la ventana principal donde se dibuja todo el contenido.
    EngineUtilities::TSharedPointer<Actor> Triangle;  // Actor que representa el tri�ngulo blanco.
    EngineUtilities::TSharedPointer<Actor> Circle;  // Actor que representa el c�rculo azul.

    sf::Clock Clock;  // Reloj para medir el tiempo entre frames (deltaTime).
    sf::Time deltaTime;  // Almacena el tiempo transcurrido entre el �ltimo frame y el actual.
};
