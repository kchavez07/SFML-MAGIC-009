#pragma once
#include "Prerequisites.h"
#include "Entity.h"
#include "ShapeFactory.h"

class Actor : Entity 
{
public:
//@brief Constructor por defecto
	Actor() = default;

	Actor(std::string actorName);

//@brief Destructor virtual
	~Actor() = default;

//@brief Actualiza el actor
//@param deltatime El tiempo transcurrido desde la ultima actualizacion 
    void update(float deltaTime) override;

//@brief Renderiza el actor 
//@param window Contexto del dispositivo para operaciones graficas
	void render(Window window) override;

//@brief Destruye el actor y libera los recuersos asociados
	void destroy();

//@brief Obtiene un componente especifico del actor
//@tparam T tipo del componente que se va a obtener
//@return Püntero compartido al componente, o nullptr si no se encuentra
	template <typename T>
	EngineUtilities::TSharedPointer<T> 
	getComponent();

private:
	std::string m_name = "Actor"; ///< Nombre del actor
};

//El proposito de esta funcion es buscar y devolver un componente especifico de un actor,
//utilizando el tipo de componente especifico como argumento de la plantilla.
//Si el componente no se encuentra, la funcion devuelve nullptr.
template<typename T>
inline EngineUtilities::TSharedPointer<T>
Actor::getComponent()
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