#pragma once
#include "Prerequisites.h"

// Declaraci�n anticipada de la clase Window (para evitar problemas de dependencias circulares).
class Window;

/*
 * Component.h
 * Esta es la clase base para todos los componentes del juego. Imagina que cada objeto en tu juego
 * tiene varias partes o "componentes" que definen su comportamiento: una posici�n, un sprite para verse bonito,
 * o incluso f�sica para interactuar con el entorno.
 *
 * Cada tipo de componente tiene un prop�sito espec�fico, y esta clase es como el "molde" del que derivan
 * todos los dem�s componentes. Los componentes individuales se encargar�n de actualizarse, dibujarse y
 * manejar su tipo seg�n lo que hagan.
 */

 // Tipos de componentes disponibles en el juego.
 // B�sicamente, estas son las "partes" que puede tener un objeto (por ejemplo, un personaje).
enum ComponentType
{
    NONE = 0,        // Un componente sin tipo (valor predeterminado).
    TRANSFORM = 1,   // Maneja la posici�n y la orientaci�n.
    SPRITE = 3,      // Le da un aspecto visual con im�genes.
    PHYSICS = 4,     // Componente para agregar f�sica (gravedad, colisiones, etc.).
    AUDIOSOURCE = 5, // Componente que se encarga del audio.
    SHAPE = 6        // Componente para mostrar formas geom�tricas.
};

// La clase `Component` es abstracta y act�a como la base para todos los componentes del juego.
// Esto significa que nunca se crear� un objeto `Component` por s� mismo; siempre ser� una subclase,
// como `TransformComponent` o `PhysicsComponent`.
class Component
{
public:
    // Constructor por defecto. No inicializa nada, solo est� aqu� como base.
    Component() = default;

    // Constructor con tipo de componente. Aqu� le decimos qu� tipo de "parte" va a representar.
    // @param type Tipo de componente que estamos creando (usa `ComponentType`).
    Component(const ComponentType type) : m_type(type) {};

    // Destructor virtual: se asegura de que la memoria se limpie correctamente
    // cuando se elimine un componente (en caso de que haya recursos adicionales).
    virtual ~Component() = default;

    // Actualiza el componente cada frame.
    // Cada componente debe tener su propia l�gica de actualizaci�n, como mover un objeto o reproducir sonido.
    // @param deltaTime El tiempo transcurrido desde la �ltima actualizaci�n (para animaciones suaves).
    virtual void update(float deltaTime) = 0;  // Nota: aseg�rate de corregir `updapte` a `update` en tus implementaciones.

    // Renderiza el componente en la ventana dada.
    // Aqu� cada componente decide c�mo quiere mostrarse en la pantalla.
    // @param window La ventana donde se va a dibujar (referencia a `Window`).
    virtual void render(Window& window) = 0;

    // Devuelve el tipo de componente que estamos manejando.
    // Esto es �til para saber con qu� tipo de "parte" estamos trabajando.
    // @return El tipo de componente (por ejemplo, `ComponentType::SPRITE`).
    ComponentType getType() const
    {
        return m_type;
    }

protected:
    ComponentType m_type;  // El tipo de componente (por ejemplo, TRANSFORM, PHYSICS, etc.)
};
