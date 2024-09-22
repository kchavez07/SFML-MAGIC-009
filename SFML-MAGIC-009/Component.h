#pragma once
#include "Prerequisites.h"

class Window;

// @enum ComponetType
// @brief Tipos de comoponentes disponibles en el juego 

enum ComponentType {
	NONE = 0,
	TRANSFORM = 1,
	SPRITE = 3,
	PHYSICS = 4,
	AUDIOSOURCE = 5,
	SHAPE = 6
};

//@class Component
//@brief Clase base abstracta para todos los componentes del juego
//Esta misma clase define la interfaz basica que todos los componentes deben implementar
//permitiendo actualizar y renderizar el componente, asi como obtener su tipo.

class Component
{
public:
	//@brief Constructor por defecto
    Component() = default;

    //constructor con tipo de component
    //type tipo del componente
	Component(const ComponentType type) : m_type(type) {};

    //Destructor Virtual 
	virtual ~Component() = default;

    //Metodo Virtual puro actualizar el componente
    //deltaTime el tiempo transcurrido desde la ultima actualizacion
	virtual void
		updapte(float deltaTime) = 0;

	//@brief Método virtual puro para renderizar el componente.
    //@param Window Contexto del dispositivo para operaciones gráficas.
    virtual void render(Window window) = 0;

	//@brief Obtiene el tipo del componente.
	//@return El tipo del componente.
    ComponentType getType() const 
	{return m_type;}

	protected:
    ComponentType m_type; // Tipo de Componente.

	};