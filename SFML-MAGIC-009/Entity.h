#pragma once
#include "Prerequisites.h"
#include "Component.h"

// Declaraci�n anticipada de la clase Window para evitar problemas de dependencias circulares.
class Window;

/*
 * Entity.h
 * La clase `Entity` es como el esqueleto de todos los objetos del juego (personajes, enemigos, etc.).
 * Imagina a una entidad como un contenedor que puede tener varias "partes" o "componentes",
 * como movimiento, apariencia, sonido, etc. Este archivo define la estructura b�sica
 * de cualquier entidad que quieras crear en el juego.
 */
class Entity
{
public:
    // Destructor virtual para asegurarse de que cualquier recurso de las subclases se limpie correctamente.
    virtual ~Entity() = default;

    // Actualiza la entidad en cada frame. 
    // Es un m�todo virtual puro, lo que significa que cada entidad debe definir c�mo se actualiza.
    // @param deltaTime El tiempo transcurrido desde la �ltima actualizaci�n (para animaciones y l�gica).
    virtual void update(float deltaTime) = 0;

    // Dibuja la entidad en la pantalla.
    // Este m�todo es abstracto y cada entidad debe implementar c�mo se quiere renderizar.
    // @param window La ventana donde se dibujar� la entidad.
    virtual void render(Window& window) = 0;

    // Agrega un nuevo componente a la entidad.
    // Los componentes son como las "partes" de la entidad que definen c�mo se comporta (f�sica, gr�ficos, etc.)
    // @tparam T Tipo de componente que queremos agregar (debe derivar de `Component`).
    // @param component Puntero compartido al componente que se quiere agregar.
    template<typename T>
    void addComponent(EngineUtilities::TSharedPointer<T> component)
    {
        // Verificamos que el tipo de `T` realmente herede de `Component`.
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
        // Guardamos el componente en nuestra lista de componentes de la entidad.
        components.push_back(component.template dynamic_pointer_cast<Component>());
    }

    // Obtiene un componente espec�fico de la entidad seg�n el tipo que buscamos.
    // Esto es �til cuando queremos interactuar con un componente en particular, como un `PhysicsComponent`.
    // @tparam T El tipo de componente que queremos obtener.
    // @return Un puntero compartido al componente, o `nullptr` si no se encuentra.
    template<typename T>
    EngineUtilities::TSharedPointer<T> getComponent()
    {
        // Recorremos todos los componentes asociados a la entidad.
        for (auto& component : components)
        {
            // Intentamos convertir cada componente al tipo espec�fico que buscamos.
            EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
            if (specificComponent)
            {
                return specificComponent;  // Si lo encontramos, lo devolvemos.
            }
        }
        // Si no se encuentra, devolvemos un puntero vac�o.
        return EngineUtilities::TSharedPointer<T>();
    }

protected:
    bool isActived;  // Indica si la entidad est� activa o no (puede ser �til para habilitar/deshabilitar entidades).
    int id;  // Identificador �nico de la entidad (�til para identificarla en el juego).

    // Vector que almacena todos los componentes asociados a esta entidad.
    std::vector<EngineUtilities::TSharedPointer<Component>> components;
};
