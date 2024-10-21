#pragma once
#include "Prerequisites.h"  // Importa las dependencias necesarias.
#include "Window.h"  // Maneja la ventana principal donde se renderiza el contenido.
#include "ShapeFactory.h"  // Provee utilidades para crear formas geométricas.
#include "Actor.h"  // Define los actores que se dibujarán en pantalla.

/**
 * @class BaseApp
 * @brief Clase principal que controla el flujo de la aplicación.
 *
 * Esta clase gestiona la ventana, los actores (como el triángulo, círculo y pista),
 * y contiene la lógica para la actualización, renderizado, movimiento y liberación de recursos.
 */
class BaseApp {
public:
    /**
     * @brief Constructor por defecto.
     *
     * No realiza ninguna inicialización adicional en este caso.
     */
    BaseApp() = default;

    /**
     * @brief Destructor por defecto.
     *
     * No se realizan liberaciones manuales, ya que se usan punteros inteligentes.
     */
    ~BaseApp() = default;

    /**
     * @brief Ejecuta la aplicación desde la función principal.
     *
     * Llama a las funciones de inicialización, actualización por frame, renderizado
     * y liberación de recursos al final de la ejecución.
     * @return int Código de salida (0 si todo salió bien).
     */
    int run();

    /**
     * @brief Inicializa los recursos necesarios para la aplicación.
     *
     * Crea la ventana principal y los actores, estableciendo sus posiciones iniciales.
     * @return true Si la inicialización fue exitosa, false en caso de error.
     */
    bool initialize();

    /**
     * @brief Actualiza la lógica de la aplicación en cada frame.
     *
     * Se encarga de gestionar el movimiento de los actores, el seguimiento del ratón,
     * y cualquier otra actualización requerida por frame.
     */
    void update();

    /**
     * @brief Renderiza los actores en la ventana.
     *
     * Dibuja los actores en la pantalla en cada frame después de la actualización.
     */
    void render();

    /**
     * @brief Libera los recursos utilizados por la aplicación.
     *
     * Se encarga de limpiar la memoria y liberar los recursos al cerrar la aplicación.
     */
    void cleanup();

    /**
     * @brief Actualiza el movimiento del círculo entre waypoints.
     *
     * Si el ratón no está cerca, el círculo se moverá automáticamente entre los waypoints.
     * @param deltaTime Tiempo entre frames utilizado para calcular el movimiento.
     * @param circle Puntero inteligente al actor del círculo.
     */
    void updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle);

private:
    Window* m_window;  ///< Puntero a la ventana principal de la aplicación.

    EngineUtilities::TSharedPointer<Actor> Triangle;  ///< Actor que representa el triángulo.
    EngineUtilities::TSharedPointer<Actor> Circle;    ///< Actor que representa el círculo.
    EngineUtilities::TSharedPointer<Actor> Track;     ///< Actor que representa la pista.

    int currentWaypoint = 0;  ///< Índice del waypoint actual en la trayectoria del círculo.
    bool isFollowingMouse = false;  ///< Indica si el círculo está siguiendo al ratón.

    /**
     * @brief Lista de waypoints que el círculo seguirá.
     *
     * Cada waypoint es un `sf::Vector2f` que representa una posición en la ventana.
     */
    std::vector<sf::Vector2f> waypoints = {
        {720.0f, 350.0f}, {720.0f, 260.0f}, {125.0f, 50.0f},
        {70.0f, 120.0f}, {70.0f, 450.0f}, {400.0f, 350.0f},
        {550.0f, 500.0f}, {650.0f, 550.0f}, {720.0f, 450.0f}
    };

    sf::Texture texture;  ///< Textura para renderizar los actores o la pista.
};
