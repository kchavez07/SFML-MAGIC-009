#pragma once
#include "Prerequisites.h"

// Declaración anticipada de la clase Window (para evitar problemas de dependencias circulares).
class Window;

/*
 * Component.h
 * Esta es la clase base para todos los componentes del juego. Imagina que cada objeto en tu juego
 * tiene varias partes o "componentes" que definen su comportamiento: una posición, un sprite para verse bonito,
 * o incluso física para interactuar con el entorno.
 *
 * Cada tipo de componente tiene un propósito específico, y esta clase es como el "molde" del que derivan
 * todos los demás componentes. Los componentes individuales se encargarán de actualizarse, dibujarse y
 * manejar su tipo según lo que hagan.
 */

 // Tipos de componentes disponibles en el juego.
 // Básicamente, estas son las "partes" que puede tener un objeto (por ejemplo, un personaje).
enum ComponentType
{
    NONE = 0,        // Un componente sin tipo (valor predeterminado).
    TRANSFORM = 1,   // Maneja la posición y la orientación.
    SPRITE = 3,      // Le da un aspecto visual con imágenes.
    PHYSICS = 4,     // Componente para agregar física (gravedad, colisiones, etc.).
    AUDIOSOURCE = 5, // Componente que se encarga del audio.
    SHAPE = 6        // Componente para mostrar formas geométricas.
};

// La clase `Component` es abstracta y actúa como la base para todos los componentes del juego.
// Esto significa que nunca se creará un objeto `Component` por sí mismo; siempre será una subclase,
// como `TransformComponent` o `PhysicsComponent`.
class Component
{
public:
    // Constructor por defecto. No inicializa nada, solo está aquí como base.
    Component() = default;

    // Constructor con tipo de componente. Aquí le decimos qué tipo de "parte" va a representar.
    // @param type Tipo de componente que estamos creando (usa `ComponentType`).
    Component(const ComponentType type) : m_type(type) {};

    // Destructor virtual: se asegura de que la memoria se limpie correctamente
    // cuando se elimine un componente (en caso de que haya recursos adicionales).
    virtual ~Component() = default;

    // Actualiza el componente cada frame.
    // Cada componente debe tener su propia lógica de actualización, como mover un objeto o reproducir sonido.
    // @param deltaTime El tiempo transcurrido desde la última actualización (para animaciones suaves).
    virtual void update(float deltaTime) = 0;  // Nota: asegúrate de corregir `updapte` a `update` en tus implementaciones.

    // Renderiza el componente en la ventana dada.
    // Aquí cada componente decide cómo quiere mostrarse en la pantalla.
    // @param window La ventana donde se va a dibujar (referencia a `Window`).
    virtual void render(Window& window) = 0;

    // Devuelve el tipo de componente que estamos manejando.
    // Esto es útil para saber con qué tipo de "parte" estamos trabajando.
    // @return El tipo de componente (por ejemplo, `ComponentType::SPRITE`).
    ComponentType getType() const
    {
        return m_type;
    }

protected:
    ComponentType m_type;  // El tipo de componente (por ejemplo, TRANSFORM, PHYSICS, etc.)
};
