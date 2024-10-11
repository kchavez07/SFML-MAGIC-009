#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

/*
 * ShapeFactory.h
 * Esta clase es como una "fábrica de formas". Se encarga de crear y manejar formas geométricas
 * (como círculos, triángulos y rectángulos) para que se puedan dibujar en la ventana.
 * Cada forma puede tener un color, una posición y ciertas interacciones.
 */
class ShapeFactory : public Component
{
public:
    // Constructor por defecto (no hace nada especial, solo inicializa la clase sin parámetros).
    ShapeFactory() = default;

    // Destructor para liberar la memoria y recursos asociados.
    virtual ~ShapeFactory() = default;

    // Constructor que inicializa la fábrica con un tipo de forma específico.
    // Por ejemplo, puedes crear un ShapeFactory que solo maneje círculos o triángulos.
    // @param shapeType Tipo de forma que manejará la fábrica (Círculo, Triángulo, etc.)
    ShapeFactory(ShapeType shapeType) :
        m_shape(nullptr), m_shapeType(ShapeType::EMPTY), Component(ComponentType::SHAPE) {};

    // Crea una nueva forma según el tipo especificado y la guarda en `m_shape`.
    // @param shapeType Tipo de forma a crear (usamos el enumerador ShapeType).
    // @return Un puntero a la forma creada (por ejemplo, un `sf::CircleShape`).
    sf::Shape* createShape(ShapeType shapeType);

    // Actualiza la forma cada frame. Por ahora no hace nada especial.
    // @param deltaTime El tiempo transcurrido desde la última actualización (usado para cálculos de animación o movimiento).
    void update(float deltaTime) override;

    // Renderiza la forma en la ventana dada. Básicamente, la dibuja en la pantalla.
    // @param window Referencia a la ventana donde queremos mostrar la forma.
    void render(Window& window) override;

    // Establece la posición de la forma usando coordenadas `x` y `y`.
    // @param x Posición en el eje X.
    // @param y Posición en el eje Y.
    void setPosition(float x, float y);

    // Otra forma de establecer la posición, pero usando un vector de SFML.
    // @param position Vector 2D que contiene las coordenadas X e Y.
    void setPosition(const sf::Vector2f& position);

    // Cambia el color de la forma (por ejemplo, rojo, azul, verde, etc.).
    // @param color Color de la forma usando `sf::Color`.
    void setFillColor(const sf::Color& color);

    // Hace que la forma se mueva hacia una posición objetivo con cierta velocidad.
    // @param targetPosition La posición objetivo a la que la forma debe dirigirse.
    // @param speed La velocidad con la que se moverá la forma.
    // @param deltaTime El tiempo transcurrido desde la última actualización (para suavizar el movimiento).
    // @param range Distancia mínima para detenerse (evita que la forma se pase del objetivo).
    void Seek(const sf::Vector2f& targetPosition, float speed, float deltaTime, float range);

    // Establece la rotación de la forma en grados.
    // @param angle Ángulo de rotación en grados.
    void setRotation(float angle);

    // Establece la escala de la forma.
    // @param scl Vector con los valores de escala en X e Y.
    void setScale(const sf::Vector2f& scl);

    // Devuelve un puntero a la forma creada.
    // Esto se usa para interactuar directamente con la forma (por ejemplo, cambiar su tamaño o color).
    // @return Un puntero a la forma (`sf::Shape*`).
    sf::Shape* getShape()
    {
        return m_shape;
    }

public:
    sf::Shape* m_shape;  // Puntero a la forma que se está manejando (puede ser un círculo, triángulo, etc.)

private:
    ShapeType m_shapeType;  // Tipo de forma que maneja esta fábrica (definido en `ShapeType`).
};
