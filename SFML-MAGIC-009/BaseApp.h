#pragma once

#include "Prerequisites.h"
#include "Window.h"
#include "Actor.h"

// @class BaseApp
// @brief Clase principal que controla el flujo de la aplicación.
// Esta clase se encarga de gestionar la ventana, los actores (como el círculo y el triángulo),
// y las funciones de renderizado, actualización y liberación de recursos.
class BaseApp
{
public:
    BaseApp() = default;  // Constructor por defecto.
    ~BaseApp() = default;  // Destructor por defecto.

    // @brief Función principal de ejecución de la aplicación.
    // Se encarga de llamar a la inicialización, el bucle de actualización y renderizado,
    // y finalmente liberar recursos cuando la aplicación finaliza.
    // @return Código de salida (normalmente 0 si todo sale bien).
    int run();

    // @brief Función de inicialización.
    // Aquí se crean la ventana principal y los actores (como el círculo y el triángulo).
    // También se define su posición y apariencia inicial.
    // @return true si la inicialización fue exitosa, false si hubo algún error.
    bool initialize();

    // @brief Función de actualización que se llama en cada frame.
    // Aquí se implementa la lógica que cambia cada vez que avanza el tiempo (como el movimiento).
    // Realiza el seguimiento del ratón y el movimiento entre los puntos predeterminados.
    void update();

    // @brief Función de renderizado que dibuja los elementos en la pantalla.
    // Se llama en cada frame después de la actualización para mostrar los actores.
    void render();

    // @brief Función de limpieza que libera los recursos y destruye la ventana.
    // Es la última función que se ejecuta cuando la aplicación está cerrando.
    void cleanup();

private:
    Window* m_window;  // Puntero a la ventana principal donde se dibuja todo el contenido.
    EngineUtilities::TSharedPointer<Actor> Triangle;  // Actor que representa el triángulo blanco.
    EngineUtilities::TSharedPointer<Actor> Circle;  // Actor que representa el círculo azul.

    sf::Clock Clock;  // Reloj para medir el tiempo entre frames (deltaTime).
    sf::Time deltaTime;  // Almacena el tiempo transcurrido entre el último frame y el actual.
};
