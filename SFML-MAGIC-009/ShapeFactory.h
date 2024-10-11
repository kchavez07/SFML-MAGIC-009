#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

/*
 * ShapeFactory.h
 * Esta clase es como una "f�brica de formas". Se encarga de crear y manejar formas geom�tricas
 * (como c�rculos, tri�ngulos y rect�ngulos) para que se puedan dibujar en la ventana.
 * Cada forma puede tener un color, una posici�n y ciertas interacciones.
 */
class ShapeFactory : public Component
{
public:
    // Constructor por defecto (no hace nada especial, solo inicializa la clase sin par�metros).
    ShapeFactory() = default;

    // Destructor para liberar la memoria y recursos asociados.
    virtual ~ShapeFactory() = default;

    // Constructor que inicializa la f�brica con un tipo de forma espec�fico.
    // Por ejemplo, puedes crear un ShapeFactory que solo maneje c�rculos o tri�ngulos.
    // @param shapeType Tipo de forma que manejar� la f�brica (C�rculo, Tri�ngulo, etc.)
    ShapeFactory(ShapeType shapeType) :
        m_shape(nullptr), m_shapeType(ShapeType::EMPTY), Component(ComponentType::SHAPE) {};

    // Crea una nueva forma seg�n el tipo especificado y la guarda en `m_shape`.
    // @param shapeType Tipo de forma a crear (usamos el enumerador ShapeType).
    // @return Un puntero a la forma creada (por ejemplo, un `sf::CircleShape`).
    sf::Shape* createShape(ShapeType shapeType);

    // Actualiza la forma cada frame. Por ahora no hace nada especial.
    // @param deltaTime El tiempo transcurrido desde la �ltima actualizaci�n (usado para c�lculos de animaci�n o movimiento).
    void update(float deltaTime) override;

    // Renderiza la forma en la ventana dada. B�sicamente, la dibuja en la pantalla.
    // @param window Referencia a la ventana donde queremos mostrar la forma.
    void render(Window& window) override;

    // Establece la posici�n de la forma usando coordenadas `x` y `y`.
    // @param x Posici�n en el eje X.
    // @param y Posici�n en el eje Y.
    void setPosition(float x, float y);

    // Otra forma de establecer la posici�n, pero usando un vector de SFML.
    // @param position Vector 2D que contiene las coordenadas X e Y.
    void setPosition(const sf::Vector2f& position);

    // Cambia el color de la forma (por ejemplo, rojo, azul, verde, etc.).
    // @param color Color de la forma usando `sf::Color`.
    void setFillColor(const sf::Color& color);

    // Hace que la forma se mueva hacia una posici�n objetivo con cierta velocidad.
    // @param targetPosition La posici�n objetivo a la que la forma debe dirigirse.
    // @param speed La velocidad con la que se mover� la forma.
    // @param deltaTime El tiempo transcurrido desde la �ltima actualizaci�n (para suavizar el movimiento).
    // @param range Distancia m�nima para detenerse (evita que la forma se pase del objetivo).
    void Seek(const sf::Vector2f& targetPosition, float speed, float deltaTime, float range);

    // Establece la rotaci�n de la forma en grados.
    // @param angle �ngulo de rotaci�n en grados.
    void setRotation(float angle);

    // Establece la escala de la forma.
    // @param scl Vector con los valores de escala en X e Y.
    void setScale(const sf::Vector2f& scl);

    // Devuelve un puntero a la forma creada.
    // Esto se usa para interactuar directamente con la forma (por ejemplo, cambiar su tama�o o color).
    // @return Un puntero a la forma (`sf::Shape*`).
    sf::Shape* getShape()
    {
        return m_shape;
    }

public:
    sf::Shape* m_shape;  // Puntero a la forma que se est� manejando (puede ser un c�rculo, tri�ngulo, etc.)

private:
    ShapeType m_shapeType;  // Tipo de forma que maneja esta f�brica (definido en `ShapeType`).
};
