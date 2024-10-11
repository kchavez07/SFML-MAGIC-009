#pragma once
#include "Prerequisites.h"
#include "Entity.h"
#include "ShapeFactory.h"
#include "Transform.h"

/*
 * Actor.h
 * La clase `Actor` es una subclase de `Entity` que representa cualquier objeto del juego que tenga
 * un nombre y un conjunto de comportamientos espec�ficos. Imagina que cada personaje, enemigo o
 * elemento del escenario es un "Actor" con su propio conjunto de componentes que definen c�mo se ve,
 * c�mo se mueve y qu� hace en el juego.
 *
 * Aqu� puedes a�adir componentes como formas geom�tricas, f�sicas, audio y m�s, y la clase `Actor`
 * se encargar� de gestionar c�mo se actualizan y se dibujan en la pantalla.
 */
class Actor : public Entity
{
public:
    // Constructor por defecto. Solo inicializa la clase sin configuraciones espec�ficas.
    Actor() = default;

    // Constructor con nombre. Crea un actor y le asigna un nombre espec�fico.
    // @param actorName Nombre del actor (puede ser cualquier cadena de texto).
    Actor(std::string actorName);

    // Destructor virtual para asegurar que cualquier recurso asociado se limpie correctamente.
    ~Actor() = default;

    // Actualiza el actor cada frame.
    // Aqu� es donde se define la l�gica de actualizaci�n, como mover el actor o gestionar su comportamiento.
    // @param deltaTime El tiempo transcurrido desde la �ltima actualizaci�n (�til para animaciones y movimientos suaves).
    void update(float deltaTime) override;

    // Renderiza el actor en la ventana dada.
    // Se asegura de que todos los componentes gr�ficos del actor se dibujen en la pantalla.
    // @param window La ventana donde se va a dibujar el actor.
    void render(Window& window) override;

    // Destruye el actor y libera todos los recursos asociados.
    // Se debe llamar a esta funci�n cuando el actor ya no es necesario en la escena.
    void destroy();

    // Obtiene un componente espec�fico del actor seg�n el tipo que buscamos.
    // Si el actor tiene, por ejemplo, un componente de tipo `Shape`, esta funci�n lo devuelve.
    // @tparam T Tipo del componente que queremos obtener (debe derivar de `Component`).
    // @return Un puntero compartido al componente, o `nullptr` si no se encuentra.
    template <typename T>
    EngineUtilities::TSharedPointer<T> getComponent();

private:
    std::string m_name = "Actor";  // Nombre del actor (�til para identificarlo en el juego).
};

// Implementaci�n del m�todo `getComponent()`.
// Este m�todo recorre todos los componentes asociados al actor y busca uno que coincida con el tipo `T`.
// Si encuentra el componente, lo devuelve. De lo contrario, devuelve un puntero vac�o (`nullptr`).
template<typename T>
inline EngineUtilities::TSharedPointer<T> Actor::getComponent()
{
    // Recorre todos los componentes del actor.
    for (auto& component : components)
    {
        // Intenta convertir el componente al tipo espec�fico que buscamos.
        EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
        if (specificComponent)
        {
            return specificComponent;  // Si lo encuentra, lo devuelve.
        }
    }
    // Devuelve un puntero vac�o si no se encuentra un componente del tipo `T`.
    return EngineUtilities::TSharedPointer<T>();
}
