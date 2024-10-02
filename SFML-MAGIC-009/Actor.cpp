#include "Prerequisites.h"
#include "Actor.h"

/*
 * Actor.cpp
 * Implementaci�n de la clase `Actor`. Aqu� es donde se definen los detalles de lo que hace un actor.
 * El actor puede tener diferentes componentes (como formas, sprites, transformaciones, etc.)
 * y se encarga de actualizarlos y dibujarlos en la pantalla seg�n se necesite.
 */

 // Constructor que inicializa un actor con un nombre espec�fico.
 // Aqu� es donde configuramos el nombre y agregamos los componentes iniciales al actor.
 // @param actorName El nombre del actor (puede ser cualquier cadena, como "Jugador1" o "Enemigo").
Actor::Actor(std::string actorName)
{
    // Guardamos el nombre del actor para identificarlo m�s f�cilmente.
    m_name = actorName;

    // Creamos un componente de tipo `ShapeFactory` para manejar formas geom�tricas.
    EngineUtilities::TSharedPointer<ShapeFactory> shape = EngineUtilities::MakeShared<ShapeFactory>();
    addComponent(shape);  // Lo a�adimos a la lista de componentes del actor.

    // Aqu� podr�amos a�adir otros componentes, como Transform, Sprite, etc.
    // Actualmente solo se agrega el componente `Shape` por simplicidad.
}

// Se llama cada frame para actualizar el actor.
// @param deltaTime El tiempo transcurrido desde la �ltima actualizaci�n (por ahora no se usa).
void Actor::update(float deltaTime)
{
    // Actualmente, esta funci�n est� vac�a porque no se ha definido ning�n comportamiento espec�fico para los actores.
    // Aqu� podr�amos manejar la l�gica de movimiento, animaciones, o reacciones del actor.
}

// Renderiza todos los componentes gr�ficos del actor en la ventana.
// @param window Referencia a la ventana donde se dibujar�n las formas del actor.
void Actor::render(Window& window)
{
    // Recorremos todos los componentes asociados al actor y dibujamos los que son de tipo `Shape`.
    for (unsigned int i = 0; i < components.size(); i++)
    {
        // Intentamos convertir cada componente a `ShapeFactory` para poder obtener la forma y dibujarla.
        window.draw(*components[i].dynamic_pointer_cast<ShapeFactory>()->getShape());
    }
}

// Destruye el actor y libera todos
