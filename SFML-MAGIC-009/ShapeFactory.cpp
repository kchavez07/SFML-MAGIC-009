#include "ShapeFactory.h"

/*
 * ShapeFactory.cpp
 * Este archivo contiene las definiciones de la clase ShapeFactory, que se encarga de crear y manipular
 * diferentes formas geom�tricas como c�rculos, rect�ngulos y tri�ngulos. Tambi�n maneja c�mo estas formas
 * se mueven y se renderizan en la ventana.
 */

 // Crea una nueva forma seg�n el tipo especificado (c�rculo, rect�ngulo, tri�ngulo, etc.)
 // y la almacena en `m_shape` para que se pueda usar despu�s.
 // @param shapeType Tipo de forma a crear (por ejemplo, CIRCLE, RECTANGLE, etc.)
 // @return Un puntero a la forma creada (sf::Shape*).
sf::Shape* ShapeFactory::createShape(ShapeType shapeType)
{
    // Guardamos el tipo de forma que vamos a manejar.
    m_shapeType = shapeType;

    // Seg�n el tipo de forma, creamos la figura correspondiente.
    switch (shapeType)
    {
    case EMPTY:
    {
        // Si la forma es "vac�a", devolvemos `nullptr`.
        return nullptr;
    }

    case CIRCLE:
    {
        // Crear un c�rculo con un radio de 10 y color blanco.
        sf::CircleShape* circle = new sf::CircleShape(10.0f);
        circle->setFillColor(sf::Color::White);
        m_shape = circle;
        return circle;
    }

    case RECTANGLE:
    {
        // Crear un rect�ngulo de 100x50 p�xeles y color blanco.
        sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(100.0f, 50.0f));
        rectangle->setFillColor(sf::Color::White);
        m_shape = rectangle;
        return rectangle;
    }

    case TRIANGLE:
    {
        // Crear un tri�ngulo usando un `CircleShape` con solo 3 puntos.
        sf::CircleShape* triangle = new sf::CircleShape(50.0f, 3);
        triangle->setFillColor(sf::Color::White);
        m_shape = triangle;
        return triangle;
    }

    default:
        return nullptr;  // Si no coincide con ning�n tipo, devolvemos `nullptr`.
    }
}

// Establece la posici�n de la forma usando coordenadas X e Y.
// @param x Posici�n en el eje X.
// @param y Posici�n en el eje Y.
void ShapeFactory::setPosition(float x, float y)
{
    if (m_shape)
    {
        m_shape->setPosition(x, y);
    }
}

// Otra forma de establecer la posici�n, pero usando un vector 2D (m�s pr�ctico a veces).
// @param position Un vector con las coordenadas X e Y.
void ShapeFactory::setPosition(const sf::Vector2f& position)
{
    if (m_shape)
    {
        m_shape->setPosition(position);
    }
}

// Establece la rotaci�n de la forma.
// @param angle �ngulo de rotaci�n en grados.
void ShapeFactory::setRotation(float angle)
{
    if (m_shape)
    {
        m_shape->setRotation(angle);
    }
}

// Establece la escala de la forma usando un vector 2D (X e Y).
// @param scl Vector que contiene la escala para los ejes X e Y.
void ShapeFactory::setScale(const sf::Vector2f& scl)
{
    if (m_shape)
    {
        m_shape->setScale(scl);
    }
}

// Cambia el color de la forma.
// Puedes usar colores predefinidos como `sf::Color::Red` o crear el tuyo con RGB.
// @param color El nuevo color de la forma.
void ShapeFactory::setFillColor(const sf::Color& color)
{
    m_shape->setFillColor(color);
}

// Hace que la forma se mueva hacia una posici�n objetivo a una velocidad espec�fica.
// @param targetPosition La posici�n objetivo a la que se mover� la forma.
// @param speed La velocidad con la que se mueve la forma (cuanto mayor el valor, m�s r�pido).
// @param deltaTime El tiempo transcurrido desde la �ltima actualizaci�n (para suavizar el movimiento).
// @param range Distancia m�nima antes de detenerse (evita que la forma se pase del objetivo).
void ShapeFactory::Seek(const sf::Vector2f& targetPosition, float speed, float deltaTime, float range)
{
    // Obtener la posici�n actual de la forma.
    sf::Vector2f shapePosition = m_shape->getPosition();

    // Calcular la direcci�n desde la forma hacia el objetivo.
    sf::Vector2f direction = targetPosition - shapePosition;

    // Calcular la distancia al objetivo (longitud del vector).
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // Si la distancia es mayor que el rango establecido, nos movemos hacia el objetivo.
    if (length > range)
    {
        // Normalizamos la direcci�n para que siempre tenga longitud 1.
        direction /= length;
        // Movemos la forma seg�n la direcci�n y la velocidad especificada.
        m_shape->move(direction * speed * deltaTime);
    }
}

// Se llama cada frame para actualizar la forma (actualmente no hace nada espec�fico).
// @param deltaTime El tiempo transcurrido desde la �ltima actualizaci�n.
void ShapeFactory::update(float deltaTime)
{
    // Aqu� se podr�an incluir actualizaciones adicionales si se necesitaran.
}

// Renderiza la forma en la ventana dada.
// @param window Referencia a la ventana donde queremos mostrar la forma.
void ShapeFactory::render(Window& window)
{
    // Si la forma existe, la dibujamos en la ventana.
    if (m_shape != nullptr)
    {
        window.draw(*m_shape);
    }
}
