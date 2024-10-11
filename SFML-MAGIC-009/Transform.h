#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

/*
 * Transform.h
 * Esta clase gestiona las transformaciones b�sicas de un actor en la escena, incluyendo su posici�n,
 * rotaci�n y escala. Estas propiedades definen c�mo se representa y transforma el actor en el mundo 2D.
 *
 * La clase `Transform` es utilizada en conjunto con otros componentes, como `ShapeFactory`, para definir
 * c�mo se mueve, rota y escala un actor en la ventana. `Transform` no se renderiza directamente, sino que
 * se utiliza para modificar los par�metros de renderizado de otros componentes.
 */
class Transform : public Component
{
public:
    // Constructor por defecto que inicializa la posici�n, rotaci�n y escala a valores por defecto.
    Transform()
        : position(0.0f, 0.0f), rotation(0.0f), scale(1.0f, 1.0f), Component(ComponentType::TRANSFORM) {}

    // Constructor con par�metros que permite inicializar las propiedades de transformaci�n.
    // @param position La posici�n inicial de la transformaci�n.
    // @param rotation La rotaci�n inicial (en grados).
    // @param scale El factor de escala inicial (por defecto es 1.0 para ambos ejes).
    Transform(const sf::Vector2f& position, float rotation = 0.0f, const sf::Vector2f& scale = sf::Vector2f(1.0f, 1.0f))
        : position(position), rotation(rotation), scale(scale), Component(ComponentType::TRANSFORM) {}

    // Destructor por defecto. No requiere liberaci�n de recursos especiales.
    virtual ~Transform() = default;

    // M�todo de actualizaci�n que se ejecuta cada frame. En esta implementaci�n, no hay l�gica que actualizar.
    // @param deltaTime El tiempo transcurrido desde el �ltimo frame (para c�lculos basados en tiempo, si es necesario).
    void update(float deltaTime) override {}

    // M�todo de renderizado. No se renderiza nada en `Transform` directamente, ya que solo almacena datos de transformaci�n.
    // @param window Referencia a la ventana (no se usa en esta implementaci�n).
    void render(Window& window) override {}

    // Establece la posici�n de la transformaci�n.
    // @param newPosition Un vector que representa la nueva posici�n en el mundo.
    void setPosition(const sf::Vector2f& newPosition)
    {
        position = newPosition;
    }

    // Establece la rotaci�n de la transformaci�n.
    // @param newRotation La nueva rotaci�n en grados.
    void setRotation(float newRotation)
    {
        rotation = newRotation;
    }

    // Establece la escala de la transformaci�n.
    // @param newScale Un vector que representa los factores de escala en X e Y.
    void setScale(const sf::Vector2f& newScale)
    {
        scale = newScale;
    }

    // Devuelve la posici�n actual de la transformaci�n.
    // @return Un vector que representa la posici�n de la entidad.
    sf::Vector2f& getPosition()
    {
        return position;
    }

    // Devuelve la rotaci�n actual de la transformaci�n.
    // @return La rotaci�n en grados.
    float getRotation() const
    {
        return rotation;
    }

    // Devuelve la escala actual de la transformaci�n.
    // @return Un vector que representa los factores de escala en X e Y.
    sf::Vector2f& getScale()
    {
        return scale;
    }

private:
    sf::Vector2f position;  // Almacena la posici�n de la entidad en el mundo.
    float rotation;         // Almacena la rotaci�n de la entidad (en un solo eje, en grados).
    sf::Vector2f scale;     // Almacena la escala de la entidad (factores de escala en X e Y).
};
