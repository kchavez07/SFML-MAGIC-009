#pragma once
#include "Prerequisites.h"

class Window;

// @enum ComponetType
// @brief Tipos de componentes disponibles en el juego 
enum ComponentType {
    NONE = 0,
    TRANSFORM = 1,
    SPRITE = 3,
    PHYSICS = 4,
    AUDIOSOURCE = 5,
    SHAPE = 6
};

// @class Component
// @brief Clase base abstracta para todos los componentes del juego
// Esta misma clase define la interfaz básica que todos los componentes deben implementar
// permitiendo actualizar y renderizar el componente, así como obtener su tipo.
class Component
{
public:
    Component() = default;

    // Constructor con tipo de componente
    Component(const ComponentType type) : m_type(type) {};

    // Destructor virtual
    virtual ~Component() = default;

    // Cambia `updapte` a `update` aquí
    virtual void update(float deltaTime) = 0;  // <--- Esta es la corrección importante

    // Método virtual puro para renderizar el componente
    virtual void render(Window& window) = 0;

    // Obtiene el tipo del componente
    ComponentType getType() const
    {
        return m_type;
    }

protected:
    ComponentType m_type;  // Tipo de Componente
};
