#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

/*
 * Transform.h
 * Esta clase gestiona las transformaciones básicas de un actor en la escena, incluyendo su posición,
 * rotación y escala. Estas propiedades definen cómo se representa y transforma el actor en el mundo 2D.
 *
 * La clase `Transform` es utilizada en conjunto con otros componentes, como `ShapeFactory`, para definir
 * cómo se mueve, rota y escala un actor en la ventana. `Transform` no se renderiza directamente, sino que
 * se utiliza para modificar los parámetros de renderizado de otros componentes.
 */
class Transform : public Component
{
public:
    // Constructor por defecto que inicializa la posición, rotación y escala a valores por defecto.
    Transform()
        : position(0.0f, 0.0f), rotation(0.0f), scale(1.0f, 1.0f), Component(ComponentType::TRANSFORM) {}

    // Constructor con parámetros que permite inicializar las propiedades de transformación.
    // @param position La posición inicial de la transformación.
    // @param rotation La rotación inicial (en grados).
    // @param scale El factor de escala inicial (por defecto es 1.0 para ambos ejes).
    Transform(const sf::Vector2f& position, float rotation = 0.0f, const sf::Vector2f& scale = sf::Vector2f(1.0f, 1.0f))
        : position(position), rotation(rotation), scale(scale), Component(ComponentType::TRANSFORM) {}

    // Destructor por defecto. No requiere liberación de recursos especiales.
    virtual ~Transform() = default;

    // Método de actualización que se ejecuta cada frame. En esta implementación, no hay lógica que actualizar.
    // @param deltaTime El tiempo transcurrido desde el último frame (para cálculos basados en tiempo, si es necesario).
    void update(float deltaTime) override {}

    // Método de renderizado. No se renderiza nada en `Transform` directamente, ya que solo almacena datos de transformación.
    // @param window Referencia a la ventana (no se usa en esta implementación).
    void render(Window& window) override {}

    // Establece la posición de la transformación.
    // @param newPosition Un vector que representa la nueva posición en el mundo.
    void setPosition(const sf::Vector2f& newPosition)
    {
        position = newPosition;
    }

    // Establece la rotación de la transformación.
    // @param newRotation La nueva rotación en grados.
    void setRotation(float newRotation)
    {
        rotation = newRotation;
    }

    // Establece la escala de la transformación.
    // @param newScale Un vector que representa los factores de escala en X e Y.
    void setScale(const sf::Vector2f& newScale)
    {
        scale = newScale;
    }

    // Devuelve la posición actual de la transformación.
    // @return Un vector que representa la posición de la entidad.
    sf::Vector2f& getPosition()
    {
        return position;
    }

    // Devuelve la rotación actual de la transformación.
    // @return La rotación en grados.
    float getRotation() const
    {
        return rotation;
    }

    // Devuelve la escala actual de la transformación.
    // @return Un vector que representa los factores de escala en X e Y.
    sf::Vector2f& getScale()
    {
        return scale;
    }

private:
    sf::Vector2f position;  // Almacena la posición de la entidad en el mundo.
    float rotation;         // Almacena la rotación de la entidad (en un solo eje, en grados).
    sf::Vector2f scale;     // Almacena la escala de la entidad (factores de escala en X e Y).
};
