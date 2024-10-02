#pragma once
#include "Prerequisites.h"
#include "Component.h"

// Declaración anticipada de la clase Window para evitar problemas de dependencias circulares.
class Window;

/*
 * Entity.h
 * La clase `Entity` es como el esqueleto de todos los objetos del juego (personajes, enemigos, etc.).
 * Imagina a una entidad como un contenedor que puede tener varias "partes" o "componentes",
 * como movimiento, apariencia, sonido, etc. Este archivo define la estructura básica
 * de cualquier entidad que quieras crear en el juego.
 */
class Entity
{
public:
    // Destructor virtual para asegurarse de que cualquier recurso de las subclases se limpie correctamente.
    virtual ~Entity() = default;

    // Actualiza la entidad en cada frame. 
    // Es un método virtual puro, lo que significa que cada entidad debe definir cómo se actualiza.
    // @param deltaTime El tiempo transcurrido desde la última actualización (para animaciones y lógica).
    virtual void update(float deltaTime) = 0;

    // Dibuja la entidad en la pantalla.
    // Este método es abstracto y cada entidad debe implementar cómo se quiere renderizar.
    // @param window La ventana donde se dibujará la entidad.
    virtual void render(Window& window) = 0;

    // Agrega un nuevo componente a la entidad.
    // Los componentes son como las "partes" de la entidad que definen cómo se comporta (física, gráficos, etc.)
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

    // Obtiene un componente específico de la entidad según el tipo que buscamos.
    // Esto es útil cuando queremos interactuar con un componente en particular, como un `PhysicsComponent`.
    // @tparam T El tipo de componente que queremos obtener.
    // @return Un puntero compartido al componente, o `nullptr` si no se encuentra.
    template<typename T>
    EngineUtilities::TSharedPointer<T> getComponent()
    {
        // Recorremos todos los componentes asociados a la entidad.
        for (auto& component : components)
        {
            // Intentamos convertir cada componente al tipo específico que buscamos.
            EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
            if (specificComponent)
            {
                return specificComponent;  // Si lo encontramos, lo devolvemos.
            }
        }
        // Si no se encuentra, devolvemos un puntero vacío.
        return EngineUtilities::TSharedPointer<T>();
    }

protected:
    bool isActived;  // Indica si la entidad está activa o no (puede ser útil para habilitar/deshabilitar entidades).
    int id;  // Identificador único de la entidad (útil para identificarla en el juego).

    // Vector que almacena todos los componentes asociados a esta entidad.
    std::vector<EngineUtilities::TSharedPointer<Component>> components;
};
