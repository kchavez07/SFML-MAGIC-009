#pragma once
#include "Prerequisites.h"
#include "Component.h"

class Window;

class Entity
{
public:
    //@brief Destructor Virtual
    virtual ~Entity() = default;

    //@brief Metodo Virtual puro para actualizar la entidad
    //@param deltaTime El tiempo Transcurrido desde la ultima actualizacion
    virtual void update(float deltatime) = 0;

    //@brief Metodo Virtual puro para renderizar la entidad
    //@param deltaTime El tiempo transcurrido desde la ultima actualizacion
    virtual void render(Window& window) = 0;

    //@brief Agrega un componente a la entidad
    //@Tparam T tipo del componente, debe derivar de `Component`
    //@param component Puntero compartido al componente que se va agregar 
    template<typename T>
    void addComponent(EngineUtilities::TSharedPointer<T> component)
    {
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
        components.push_back(component.template dynamic_pointer_cast<Component>());
    }

    //@brief Obtiene un componente de la entidad
    //@tparam T Tipo del componente que se va a obtener 
    //@return Puntero compartido al componente, o nullptr si no se encuentra 
    template<typename T>
    EngineUtilities::TSharedPointer<T> getComponent()
    {
        for (auto& component : components)
        {
            EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
            if (specificComponent)
            {
                return specificComponent;
            }
        }
        return EngineUtilities::TSharedPointer<T>();
    }

protected:
    bool isActived;
    int id;

    // Vector que almacena los componentes asociados a la entidad
    std::vector<EngineUtilities::TSharedPointer<Component>> components;
};
