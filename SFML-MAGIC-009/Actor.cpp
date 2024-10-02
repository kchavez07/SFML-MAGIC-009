#include "Prerequisites.h"
#include "Actor.h"

/*
 * Actor.cpp
 * Implementación de la clase `Actor`. Aquí es donde se definen los detalles de lo que hace un actor.
 * El actor puede tener diferentes componentes (como formas, sprites, transformaciones, etc.)
 * y se encarga de actualizarlos y dibujarlos en la pantalla según se necesite.
 */

 // Constructor que inicializa un actor con un nombre específico.
 // Aquí es donde configuramos el nombre y agregamos los componentes iniciales al actor.
 // @param actorName El nombre del actor (puede ser cualquier cadena, como "Jugador1" o "Enemigo").
Actor::Actor(std::string actorName)
{
    // Guardamos el nombre del actor para identificarlo más fácilmente.
    m_name = actorName;

    // Creamos un componente de tipo `ShapeFactory` para manejar formas geométricas.
    EngineUtilities::TSharedPointer<ShapeFactory> shape = EngineUtilities::MakeShared<ShapeFactory>();
    addComponent(shape);  // Lo añadimos a la lista de componentes del actor.

    // Aquí podríamos añadir otros componentes, como Transform, Sprite, etc.
    // Actualmente solo se agrega el componente `Shape` por simplicidad.
}

// Se llama cada frame para actualizar el actor.
// @param deltaTime El tiempo transcurrido desde la última actualización (por ahora no se usa).
void Actor::update(float deltaTime)
{
    // Actualmente, esta función está vacía porque no se ha definido ningún comportamiento específico para los actores.
    // Aquí podríamos manejar la lógica de movimiento, animaciones, o reacciones del actor.
}

// Renderiza todos los componentes gráficos del actor en la ventana.
// @param window Referencia a la ventana donde se dibujarán las formas del actor.
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
