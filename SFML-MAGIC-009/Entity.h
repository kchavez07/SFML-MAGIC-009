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
	virtual void
		update(float deltatime) = 0;

//@brief Metodo Virtual puro poara renderizar la entidad
//@param deltaTime El tiempo transcurrido desde la ultima actualizacion
	virtual void
		render(Window window) = 0;

//@brief Agrega un componente a la entidad
//@Tparam T tipo del component, debe derivar de Comnponet
//@param component Puntero compartido al componente que se va agregar 
	template<typename T>
	void addComponent(EngineUtilities::TSharedPointer<T>component)
	{
		static_assert(std::is_base_of_<Component, T>::value, "T must be derivedfrom Component");
		components.push_back(component);
	}

//@brief Obtiene un componente de la entidad
//@tparam T Tipo del component que se va a obtener 
//@Return Puntero compartido al componente, o nullptr si no se encuentra 

	template<typename T>
	EngineUtilities::TSharedPointer<T>
	getComponet() 
	{
		for (auto& component : components) 
		{
			EngineUtilities::TSharedPointer<T> specificComponent = std::dynamic_pointer_cast<T>(component);
			if (specificComponent) 
			{
				return specificComponent;
			}
		}
		return nullptr;
	}

protected:
	  bool isActived;
	  int id;

	  std::vector<EngineUtilities::TSharedPointer<Component>> components;
};