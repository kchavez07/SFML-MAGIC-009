#pragma once 
#include "Prerequisites.h"  // Incluye las bibliotecas y dependencias esenciales.

/**
 * @class Window
 * @brief Clase que gestiona la ventana principal del proyecto.
 *
 * Esta clase controla la creaci�n, actualizaci�n, renderizado y destrucci�n
 * de la ventana utilizando la biblioteca SFML. Tambi�n maneja el tiempo entre
 * frames para c�lculos precisos y permite manipular la vista de la ventana.
 */
class Window {
public:
    /**
     * @brief Constructor por defecto.
     *
     * No realiza ninguna operaci�n especial.
     */
    Window() = default;

    /**
     * @brief Constructor parametrizado.
     *
     * Crea una ventana con las dimensiones y t�tulo especificados.
     *
     * @param width Ancho de la ventana.
     * @param height Altura de la ventana.
     * @param title T�tulo de la ventana.
     */
    Window(int width, int height, const std::string& title);

    /**
     * @brief Destructor de la clase.
     *
     * Libera los recursos utilizados por la ventana.
     */
    ~Window();

    /**
     * @brief Maneja los eventos de la ventana.
     *
     * Procesa eventos como cerrar, minimizar o mover la ventana.
     */
    void handleEvents();

    /**
     * @brief Limpia el contenido de la ventana.
     *
     * Prepara la ventana para dibujar nuevos elementos en el siguiente frame.
     */
    void clear();

    /**
     * @brief Muestra en pantalla el contenido dibujado.
     *
     * Realiza un "flip" para actualizar la ventana con el contenido m�s reciente.
     */
    void display();

    /**
     * @brief Verifica si la ventana sigue abierta.
     *
     * @return true si la ventana est� abierta, false si se ha cerrado.
     */
    bool isOpen() const;

    /**
     * @brief Dibuja un objeto en la ventana.
     *
     * Recibe cualquier objeto que herede de `sf::Drawable` para dibujarlo.
     *
     * @param drawable Objeto a dibujar (como un c�rculo o rect�ngulo).
     */
    void draw(const sf::Drawable& drawable);

    /**
     * @brief Obtiene el puntero a la ventana interna de SFML.
     *
     * Esto permite interactuar directamente con la ventana de SFML.
     *
     * @return Un puntero al objeto `sf::RenderWindow`.
     */
    sf::RenderWindow* getWindow();

    /**
     * @brief Inicializa la ventana.
     *
     * Realiza la configuraci�n inicial necesaria para mostrar la ventana.
     */
    void init();

    /**
     * @brief Actualiza la l�gica de la ventana cada frame.
     *
     * Usa el `deltaTime` para calcular el tiempo transcurrido entre frames
     * y actualizar animaciones o movimientos.
     */
    void update();

    /**
     * @brief Renderiza el contenido de la ventana.
     *
     * Dibuja todos los elementos que deben mostrarse en la ventana.
     */
    void render();

    /**
     * @brief Destruye la ventana y libera los recursos.
     *
     * Llama a las funciones necesarias para cerrar la ventana correctamente.
     */
    void destroy();

private:
    sf::RenderWindow* m_window;  ///< Puntero a la ventana de SFML donde se dibujan los elementos.
    sf::View m_view;  ///< Vista de la ventana para manipular la c�mara o perspectiva.

public:
    sf::Time deltaTime;  ///< Tiempo transcurrido entre frames.
    sf::Clock clock;  ///< Reloj para medir el tiempo entre frames.
};
