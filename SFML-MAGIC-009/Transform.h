#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

/*
 * Transform.h
 * Esta clase gestiona las transformaciones básicas de un actor en la escena, incluyendo su posición,
 * rotación y escala. Estas propiedades definen cómo se representa y transforma el actor en el mundo 2D.
 */
class Transform : public Component
{
public:
    // Constructor por defecto que inicializa la posición, rotación y escala a valores por defecto.
    Transform()
        : position(0.0f, 0.0f), rotation(0.0f), scale(1.0f, 1.0f), Component(ComponentType::TRANSFORM) {}

    // Constructor con parámetros que permite inicializar las propiedades de transformación.
    Transform(const sf::Vector2f& position, float rotation = 0.0f, const sf::Vector2f& scale = sf::Vector2f(1.0f, 1.0f))
        : position(position), rotation(rotation), scale(scale), Component(ComponentType::TRANSFORM) {}

    // Destructor por defecto. No requiere liberación de recursos especiales.
    virtual ~Transform() = default;

    // Actualiza el estado del componente (no hace nada en esta implementación).
    void update(float deltaTime) override {}

    // Renderiza el componente (no aplicable para Transform).
    void render(Window& window) override {}

    // Establece la posición del actor.
    void setPosition(const sf::Vector2f& newPosition) {
        position = newPosition;
    }

    // Establece la rotación del actor.
    void setRotation(float newRotation) {
        rotation = newRotation;
    }

    // Establece la escala del actor.
    void setScale(const sf::Vector2f& newScale) {
        scale = newScale;
    }

    // Devuelve la posición actual del actor.
    sf::Vector2f& getPosition() {
        return position;
    }

    // Devuelve la rotación actual del actor.
    float getRotation() const {
        return rotation;
    }

    // Devuelve la escala actual del actor.
    sf::Vector2f& getScale() {
        return scale;
    }

    /**
     * @brief Mueve la entidad hacia un objetivo con una velocidad específica.
     *
     * @param targetPosition La posición objetivo hacia la que se moverá.
     * @param speed La velocidad a la que se moverá la entidad.
     * @param deltaTime El tiempo transcurrido entre frames para un movimiento suave.
     * @param range La distancia mínima antes de detener el movimiento.
     */
    void Seek(const sf::Vector2f& targetPosition, float speed, float deltaTime, float range) {
        // Calcular la dirección hacia el objetivo.
        sf::Vector2f direction = targetPosition - position;

        // Calcular la distancia al objetivo.
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        // Si estamos dentro del rango, no realizamos más movimiento.
        if (distance < range) return;

        // Normalizamos la dirección.
        if (distance > 0.0f) {
            direction /= distance;
        }

        // Mover la posición según la dirección, velocidad y deltaTime.
        position += direction * speed * deltaTime;
    }

private:
    sf::Vector2f position;  // Posición del actor.
    float rotation;         // Rotación del actor en grados.
    sf::Vector2f scale;     // Escala del actor en los ejes X e Y.
};
