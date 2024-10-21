#pragma once
#include "Prerequisites.h"  // Incluye dependencias esenciales.
#include "Component.h"       // Define la clase base Component.
#include "Window.h"          // Clase para gestionar la ventana principal.

/**
 * @class ShapeFactory
 * @brief Fábrica de formas geométricas.
 *
 * La clase `ShapeFactory` permite la creación y gestión de formas geométricas como círculos,
 * rectángulos y triángulos. Además, facilita la manipulación de propiedades como posición,
 * color, rotación y escala de dichas formas, y su posterior renderizado en la ventana.
 */
class ShapeFactory : public Component {
public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa la clase sin realizar ninguna acción adicional.
     */
    ShapeFactory() = default;

    /**
     * @brief Destructor virtual por defecto.
     *
     * Se asegura que cualquier recurso asignado por las clases hijas
     * sea liberado correctamente.
     */
    virtual ~ShapeFactory() = default;

    /**
     * @brief Constructor parametrizado.
     *
     * Inicializa la fábrica con un tipo específico de forma a gestionar.
     *
     * @param shapeType Tipo de forma que será creada (CIRCLE, RECTANGLE, etc.).
     */
    ShapeFactory(ShapeType shapeType);

    /**
     * @brief Crea una nueva forma geométrica según el tipo indicado.
     *
     * Asigna la forma creada al puntero `m_shape` para su posterior manipulación.
     *
     * @param shapeType El tipo de forma a crear.
     * @return Puntero a la forma creada (`sf::Shape*`).
     */
    sf::Shape* createShape(ShapeType shapeType);

    /**
     * @brief Actualiza el estado de la forma en cada frame.
     *
     * Este método permite manejar animaciones o transiciones de la forma.
     *
     * @param deltaTime Tiempo transcurrido desde el último frame.
     */
    void update(float deltaTime) override;

    /**
     * @brief Renderiza la forma en la ventana proporcionada.
     *
     * Dibuja la forma en pantalla en cada frame.
     *
     * @param window Ventana donde se renderiza la forma.
     */
    void render(Window& window) override;

    /**
     * @brief Establece la posición de la forma con coordenadas X e Y.
     *
     * @param x Coordenada X.
     * @param y Coordenada Y.
     */
    void setPosition(float x, float y);

    /**
     * @brief Establece la posición de la forma con un vector 2D.
     *
     * @param position Un vector que contiene las coordenadas X e Y.
     */
    void setPosition(const sf::Vector2f& position);

    /**
     * @brief Cambia el color de la forma.
     *
     * @param color El nuevo color de la forma.
     */
    void setFillColor(const sf::Color& color);

    /**
     * @brief Establece la rotación de la forma en grados.
     *
     * @param angle Ángulo de rotación.
     */
    void setRotation(float angle);

    /**
     * @brief Establece la escala de la forma en los ejes X e Y.
     *
     * @param scl Vector con los valores de escala en X e Y.
     */
    void setScale(const sf::Vector2f& scl);

    /**
     * @brief Obtiene la forma creada.
     *
     * @return Puntero a la forma creada (`sf::Shape*`).
     */
    sf::Shape* getShape();

private:
    sf::Shape* m_shape = nullptr;  ///< Puntero a la forma gestionada por esta fábrica.
    ShapeType m_shapeType = ShapeType::EMPTY;  ///< Tipo de forma gestionada.
};
