#pragma once
#include "Prerequisites.h"  // Importa las dependencias necesarias.
#include "Window.h"  // Maneja la ventana principal donde se renderiza el contenido.
#include "ShapeFactory.h"  // Provee utilidades para crear formas geom�tricas.
#include "Actor.h"  // Define los actores que se dibujar�n en pantalla.

/**
 * @class BaseApp
 * @brief Clase principal que controla el flujo de la aplicaci�n.
 *
 * Esta clase gestiona la ventana, los actores (como el tri�ngulo, c�rculo y pista),
 * y contiene la l�gica para la actualizaci�n, renderizado, movimiento y liberaci�n de recursos.
 */
class BaseApp {
public:
    /**
     * @brief Constructor por defecto.
     *
     * No realiza ninguna inicializaci�n adicional en este caso.
     */
    BaseApp() = default;

    /**
     * @brief Destructor por defecto.
     *
     * No se realizan liberaciones manuales, ya que se usan punteros inteligentes.
     */
    ~BaseApp() = default;

    /**
     * @brief Ejecuta la aplicaci�n desde la funci�n principal.
     *
     * Llama a las funciones de inicializaci�n, actualizaci�n por frame, renderizado
     * y liberaci�n de recursos al final de la ejecuci�n.
     * @return int C�digo de salida (0 si todo sali� bien).
     */
    int run();

    /**
     * @brief Inicializa los recursos necesarios para la aplicaci�n.
     *
     * Crea la ventana principal y los actores, estableciendo sus posiciones iniciales.
     * @return true Si la inicializaci�n fue exitosa, false en caso de error.
     */
    bool initialize();

    /**
     * @brief Actualiza la l�gica de la aplicaci�n en cada frame.
     *
     * Se encarga de gestionar el movimiento de los actores, el seguimiento del rat�n,
     * y cualquier otra actualizaci�n requerida por frame.
     */
    void update();

    /**
     * @brief Renderiza los actores en la ventana.
     *
     * Dibuja los actores en la pantalla en cada frame despu�s de la actualizaci�n.
     */
    void render();

    /**
     * @brief Libera los recursos utilizados por la aplicaci�n.
     *
     * Se encarga de limpiar la memoria y liberar los recursos al cerrar la aplicaci�n.
     */
    void cleanup();

    /**
     * @brief Actualiza el movimiento del c�rculo entre waypoints.
     *
     * Si el rat�n no est� cerca, el c�rculo se mover� autom�ticamente entre los waypoints.
     * @param deltaTime Tiempo entre frames utilizado para calcular el movimiento.
     * @param circle Puntero inteligente al actor del c�rculo.
     */
    void updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle);

private:
    Window* m_window;  ///< Puntero a la ventana principal de la aplicaci�n.

    EngineUtilities::TSharedPointer<Actor> Triangle;  ///< Actor que representa el tri�ngulo.
    EngineUtilities::TSharedPointer<Actor> Circle;    ///< Actor que representa el c�rculo.
    EngineUtilities::TSharedPointer<Actor> Track;     ///< Actor que representa la pista.

    int currentWaypoint = 0;  ///< �ndice del waypoint actual en la trayectoria del c�rculo.
    bool isFollowingMouse = false;  ///< Indica si el c�rculo est� siguiendo al rat�n.

    /**
     * @brief Lista de waypoints que el c�rculo seguir�.
     *
     * Cada waypoint es un `sf::Vector2f` que representa una posici�n en la ventana.
     */
    std::vector<sf::Vector2f> waypoints = {
        {720.0f, 350.0f}, {720.0f, 260.0f}, {125.0f, 50.0f},
        {70.0f, 120.0f}, {70.0f, 450.0f}, {400.0f, 350.0f},
        {550.0f, 500.0f}, {650.0f, 550.0f}, {720.0f, 450.0f}
    };

    sf::Texture texture;  ///< Textura para renderizar los actores o la pista.
};
