#include "Window.h"
#include "Prerequisites.h"

/*
 * Window.cpp
 * Implementación de la clase Window. Aquí definimos cómo se comporta nuestra ventana en la práctica.
 * Se encarga de crear, actualizar y destruir la ventana de SFML. Además, gestiona todo lo que sucede
 * dentro de ella, como eventos del usuario, y muestra los gráficos en pantalla.
 */

 // Constructor que crea una ventana con un tamaño específico y un título.
 // @param width Ancho de la ventana en píxeles.
 // @param height Alto de la ventana en píxeles.
 // @param title Título que se mostrará en la barra de la ventana.
Window::Window(int width, int height, const std::string& title)
{
    // Creamos la ventana con los parámetros dados usando SFML.
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

    // Comprobamos si la ventana se creó correctamente.
    if (!m_window) {
        ERROR("Window", "Window", "CHECK CONSTRUCTOR");  // Si falla, mostramos un error.
    }
    else {
        MESSAGE("WIndow", "Window", "OK");  // Si se creó bien, confirmamos con un mensaje.
    }
}

// Destructor de la ventana.
// Aquí liberamos la memoria asignada a la ventana para evitar fugas de memoria.
Window::~Window() {
    delete m_window;
}

// Manejador de eventos: esta función se llama cada frame para ver qué está haciendo el usuario.
// Por ejemplo, si el usuario cierra la ventana o hace clic en algún botón.
void Window::handleEvents()
{
    sf::Event event;
    // Recorremos todos los eventos pendientes (clics, teclas, etc.) y los gestionamos.
    while (m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)  // Si el evento es "cerrar ventana", la cerramos.
            m_window->close();
    }
}

// Limpia la ventana con el color predeterminado.
// Básicamente, borra todo lo que se ve actualmente para que podamos dibujar las cosas nuevas.
void Window::clear()
{
    if (m_window != nullptr) {
        m_window->clear();  // Limpiamos la ventana.
    }
    else {
        ERROR("Window", "clear", "CHECK FOR WINDOW POINTER DATA");  // Si no hay ventana, error.
    }
}

// Muestra en la pantalla lo que hemos dibujado.
// Aquí es donde realmente se "hace visible" todo lo que hemos puesto en la ventana.
void Window::display()
{
    if (m_window != nullptr) {
        m_window->display();  // Actualizamos la pantalla.
    }
    else {
        ERROR("Window", "display", "CHECK FOR WINDOW POINTER DATA");  // Error si no hay ventana.
    }
}

// Verifica si la ventana sigue abierta.
// Esto nos permite saber si debemos seguir dibujando o si ya no hay ventana disponible.
bool Window::isOpen() const
{
    if (m_window != nullptr) {
        return m_window->isOpen();  // Devolvemos el estado de la ventana.
    }
    else {
        ERROR("Window", "isOpen", "CHECK FOR WINDOW POINTER DATA");  // Error si no hay ventana.
        return false;
    }
}

// Dibuja en la ventana cualquier cosa que pueda ser renderizada (círculos, rectángulos, etc.)
// @param drawable El objeto que queremos mostrar (hereda de sf::Drawable).
void Window::draw(const sf::Drawable& drawable)
{
    if (m_window != nullptr) {
        m_window->draw(drawable);  // Dibujamos el objeto en la ventana.
    }
    else {
        ERROR("Window", "draw", "CHECK FOR WINDOW POINTER DATA");  // Error si no hay ventana.
    }
}

// Devuelve un puntero a la ventana real de SFML.
// Esto nos permite hacer cosas específicas con la ventana de SFML si lo necesitamos.
sf::RenderWindow* Window::getWindow()
{
    if (m_window != nullptr) {
        return m_window;  // Devolvemos el puntero a la ventana.
    }
    else {
        ERROR("Window", "getWindow", "CHECK FOR WINDOW POINTER DATA");  // Error si no hay ventana.
        return nullptr;
    }
}

// Libera todos los recursos de la ventana y la destruye.
// Después de llamar a esta función, la ventana deja de existir.
void Window::destroy()
{
    SAFE_PTR_RELEASE(m_window);  // Usamos la macro para liberar memoria de forma segura.
}

// Inicializa la ventana (por ahora, no hace nada especial).
// Si en el futuro queremos hacer algo al inicio, lo pondríamos aquí.
void Window::init()
{
}

// Actualiza la ventana cada frame (todavía no tiene funcionalidad específica).
void Window::updapte()
{
}

// Renderiza el contenido de la ventana (todavía no tiene funcionalidad específica).
void Window::render()
{
}
