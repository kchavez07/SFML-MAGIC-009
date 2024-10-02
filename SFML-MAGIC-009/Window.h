#pragma once
#include "Prerequisites.h"

/*
 * Window.h
 * Esta clase gestiona la ventana principal donde se dibujan todos los elementos gráficos del proyecto.
 * Maneja la creación, renderizado y actualización de la ventana de SFML.
 * Básicamente, es la encargada de mantener "vivo" el espacio donde se mostrarán nuestros gráficos.
 */
class Window
{
public:
    // Constructor por defecto (no hace nada especial, pero está aquí por si necesitamos una ventana sin parámetros).
    Window() = default;

    // Constructor principal que crea una ventana con un tamaño específico y un título personalizado.
    // @param width Ancho de la ventana.
    // @param height Altura de la ventana.
    // @param title Título de la ventana.
    Window(int width, int height, const std::string& title);

    // Destructor para liberar los recursos de la ventana cuando ya no los necesitamos.
    ~Window();

    // Se encarga de manejar los eventos de la ventana (como cerrar, minimizar, mover, etc.).
    // Básicamente, escucha lo que el usuario hace con la ventana.
    void handleEvents();

    // Limpia la ventana, es decir, borra todo lo que está actualmente en la pantalla.
    // Por lo general, se usa para preparar el área antes de volver a dibujar todo.
    void clear();

    // Muestra en la pantalla el contenido que hemos dibujado hasta ahora.
    // Es como un "flip" que actualiza la ventana con las últimas imágenes.
    void display();

    // Verifica si la ventana sigue abierta.
    // @return true si está abierta y podemos dibujar en ella, false si se cerró.
    bool isOpen() const;

    // Dibuja cualquier objeto que pueda ser mostrado en la ventana.
    // SFML usa `sf::Drawable` como base para todos los objetos que se pueden dibujar.
    // @param drawable Referencia a un objeto que SFML puede dibujar (como un círculo, rectángulo, etc.).
    void draw(const sf::Drawable& drawable);

    // Devuelve el puntero a la ventana interna de SFML (la verdadera ventana que se muestra en pantalla).
    // Esto es útil si necesitamos interactuar directamente con la ventana de SFML.
    // @return Puntero al objeto `sf::RenderWindow`.
    sf::RenderWindow* getWindow();

    // Inicializa la ventana y la configura con los parámetros que le hemos pasado.
    // Esto es lo primero que se debe hacer para crear la ventana antes de usarla.
    void init();

    // Actualiza la ventana cada frame. 
    // Aquí se podrían manejar cosas como animaciones, entradas del usuario, etc.
    void updapte();  // Nota: Parece que `updapte` está mal escrito. Debe ser `update`.

    // Renderiza el contenido de la ventana (dibuja todo lo que se necesita ver).
    void render();

    // Libera todos los recursos de la ventana. 
    // Útil cuando queremos cerrar la aplicación y asegurarnos de que no queden cosas pendientes.
    void destroy();

private:
    sf::RenderWindow* m_window;  // La ventana de SFML donde realmente se muestran nuestros gráficos.
};
