#include "Window.h"
#include "Prerequisites.h"

Window::Window(int width, int height, const std::string& title) 
{
	m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

	if (!m_window) {
		ERROR("Window", "Window", "CHECK CONSTRUCTOR");
	}
	else {
		MESSAGE("WIndow", "Window", "OK")
	}
}

Window::~Window() {
	delete m_window;
}

void Window::handleEvents()
{
sf::Event event;
while (m_window->pollEvent(event))
    {
	if (event.type == sf::Event::Closed)
		m_window->close();
    }
 }

void Window::clear()
{
	if (m_window != nullptr) {
      m_window->clear();
	}
	else {
		ERROR("Window", "clear", "CHECK FOR WINDOW PONTER DATA");
    }
}

void Window::display() 
{
	if (m_window != nullptr) {
		m_window->clear();
	}
	else {
		ERROR("Window", "display", "CHECK FOR WINDOW PONTER DATA");
	}
}

bool Window::isOpen() const
{
	if (m_window != nullptr) {
		m_window->isOpen();
	}
	else {
		ERROR("Window", "isOpen", "CHECK FOR WINDOW PONTER DATA");
	    return false;
	}	
}

void Window::draw(const sf::Drawable& drawable)
{
	if (m_window != nullptr) {
		m_window->draw(drawable);
	}
	else {
		ERROR("Window", "draw", "CHECK FOR WINDOW PONTER DATA");
	}
}

sf::RenderWindow* Window::getWindow()
{
	if (m_window != nullptr) {
		return m_window;
	}
	else {
		return nullptr;
		ERROR("Window", "getWidow", "CHECK FOR WINDOW PONTER DATA");
	}
}
