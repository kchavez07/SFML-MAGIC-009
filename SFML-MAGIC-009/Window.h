#pragma once
#include "Prerequisites.h"

/*
 * Window.h
 * Esta clase gestiona la ventana principal donde se dibujan todos los elementos gr�ficos del proyecto.
 * Maneja la creaci�n, renderizado y actualizaci�n de la ventana de SFML.
 * B�sicamente, es la encargada de mantener "vivo" el espacio donde se mostrar�n nuestros gr�ficos.
 */
class Window
{
public:
    // Constructor por defecto (no hace nada especial, pero est� aqu� por si necesitamos una ventana sin par�metros).
    Window() = default;

    // Constructor principal que crea una ventana con un tama�o espec�fico y un t�tulo personalizado.
    // @param width Ancho de la ventana.
    // @param height Altura de la ventana.
    // @param title T�tulo de la ventana.
    Window(int width, int height, const std::string& title);

    // Destructor para liberar los recursos de la ventana cuando ya no los necesitamos.
    ~Window();

    // Se encarga de manejar los eventos de la ventana (como cerrar, minimizar, mover, etc.).
    // B�sicamente, escucha lo que el usuario hace con la ventana.
    void handleEvents();

    // Limpia la ventana, es decir, borra todo lo que est� actualmente en la pantalla.
    // Por lo general, se usa para preparar el �rea antes de volver a dibujar todo.
    void clear();

    // Muestra en la pantalla el contenido que hemos dibujado hasta ahora.
    // Es como un "flip" que actualiza la ventana con las �ltimas im�genes.
    void display();

    // Verifica si la ventana sigue abierta.
    // @return true si est� abierta y podemos dibujar en ella, false si se cerr�.
    bool isOpen() const;

    // Dibuja cualquier objeto que pueda ser mostrado en la ventana.
    // SFML usa `sf::Drawable` como base para todos los objetos que se pueden dibujar.
    // @param drawable Referencia a un objeto que SFML puede dibujar (como un c�rculo, rect�ngulo, etc.).
    void draw(const sf::Drawable& drawable);

    // Devuelve el puntero a la ventana interna de SFML (la verdadera ventana que se muestra en pantalla).
    // Esto es �til si necesitamos interactuar directamente con la ventana de SFML.
    // @return Puntero al objeto `sf::RenderWindow`.
    sf::RenderWindow* getWindow();

    // Inicializa la ventana y la configura con los par�metros que le hemos pasado.
    // Esto es lo primero que se debe hacer para crear la ventana antes de usarla.
    void init();

    // Actualiza la ventana cada frame. 
    // Aqu� se podr�an manejar cosas como animaciones, entradas del usuario, etc.
    void updapte();  // Nota: Parece que `updapte` est� mal escrito. Debe ser `update`.

    // Renderiza el contenido de la ventana (dibuja todo lo que se necesita ver).
    void render();

    // Libera todos los recursos de la ventana. 
    // �til cuando queremos cerrar la aplicaci�n y asegurarnos de que no queden cosas pendientes.
    void destroy();

private:
    sf::RenderWindow* m_window;  // La ventana de SFML donde realmente se muestran nuestros gr�ficos.
};
