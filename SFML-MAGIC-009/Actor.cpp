#include "Prerequisites.h"
#include "Actor.h"

/*
 * Actor.cpp
 * Implementación de la clase `Actor`. Esta clase representa cualquier entidad gráfica en el juego
 * que puede tener múltiples componentes como formas, transformaciones y comportamientos específicos.
 * Cada actor tiene la capacidad de actualizarse y renderizarse, así como almacenar y gestionar múltiples componentes.
 * Se ha agregado la clase `Transform` para manejar la posición, rotación y escala de los actores de manera eficiente.
 */

 // Constructor que inicializa un actor con un nombre específico.
 // Aquí se define el nombre del actor y se agregan componentes básicos como `ShapeFactory` y `Transform`.
 // @param actorName Nombre del actor que será utilizado para su identificación.
Actor::Actor(std::string actorName)
{
    // Guardamos el nombre del actor para identificarlo fácilmente durante el desarrollo y la depuración.
    m_name = actorName;

    // Creación del componente `ShapeFactory` que se encargará de definir las formas geométricas del actor.
    EngineUtilities::TSharedPointer<ShapeFactory> shape = EngineUtilities::MakeShared<ShapeFactory>();
    addComponent(shape);  // Añadimos `ShapeFactory` a la lista de componentes del actor.

    // Creación del componente `Transform` que gestiona la posición, rotación y escala del actor.
    // Este componente permite manipular las transformaciones espaciales del actor.
    EngineUtilities::TSharedPointer<Transform> transform = EngineUtilities::MakeShared<Transform>();
    addComponent(transform);  // Agregamos el componente `Transform` al actor para manejar sus transformaciones.

    // Actualmente, el actor solo tiene dos componentes: `ShapeFactory` y `Transform`.
    // En el futuro, se pueden agregar otros componentes como `Sprite`, `Physics`, `AudioSource`, etc.,
    // para extender el comportamiento del actor según sea necesario.
}

// Función `update` que se llama en cada frame para actualizar la lógica interna del actor.
// @param deltaTime El tiempo transcurrido desde la última actualización.
// Este parámetro es útil para realizar animaciones y cálculos basados en tiempo real.
void Actor::update(float deltaTime)
{
    // Obtener el componente de transformaciones y el de forma del actor
    auto transform = getComponent<Transform>();
    auto shape = getComponent<ShapeFactory>();

    // Actualizar la posición, rotación y escala del actor si ambos componentes están presentes
    if (transform && shape)
    {
        shape->setPosition(transform->getPosition());   // Actualiza la posición de la forma basada en el componente de Transform
        shape->setRotation(transform->getRotation());   // Actualiza la rotación de la forma
        shape->setScale(transform->getScale());         // Actualiza la escala de la forma
    }
}

// Renderiza todos los componentes gráficos del actor en la ventana especificada.
// @param window Referencia a la ventana donde se dibujarán los componentes gráficos del actor.
void Actor::render(Window& window)
{
    // Recorremos todos los componentes asociados al actor y verificamos si son de tipo `ShapeFactory`.
    // Si lo son, obtenemos la forma (`Shape`) y la dibujamos en la ventana.
    for (unsigned int i = 0; i < components.size(); i++)
    {
        // `dynamic_pointer_cast` se usa para convertir de manera segura el componente a `ShapeFactory`.
        // Si la conversión es exitosa, se dibuja la forma correspondiente.
        if (components[i].dynamic_pointer_cast<ShapeFactory>())
        {
            window.draw(*components[i].dynamic_pointer_cast<ShapeFactory>()->getShape());
        }
    }
}

// Destruye el actor y libera todos los recursos asociados a sus componentes.
// La liberación de recursos es crucial para evitar fugas de memoria y mantener el rendimiento del juego.
// En esta implementación, la gestión de memoria se realiza de manera automática gracias a los punteros inteligentes.
void Actor::destroy()
{
    // Esta función está preparada para liberar cualquier recurso adicional si es necesario.
    // Actualmente, no es necesario liberar manualmente los componentes porque se manejan con `TSharedPointer`.
}
