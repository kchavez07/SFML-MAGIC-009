#pragma once
#include "Prerequisites.h"  // Incluye dependencias esenciales.
#include "Component.h"       // Define la clase base Component.
#include "Window.h"          // Clase para gestionar la ventana principal.

/**
 * @class ShapeFactory
 * @brief F�brica de formas geom�tricas.
 *
 * La clase `ShapeFactory` permite la creaci�n y gesti�n de formas geom�tricas como c�rculos,
 * rect�ngulos y tri�ngulos. Adem�s, facilita la manipulaci�n de propiedades como posici�n,
 * color, rotaci�n y escala de dichas formas, y su posterior renderizado en la ventana.
 */
class ShapeFactory : public Component {
public:
    /**
     * @brief Constructor por defecto.
     *
     * Inicializa la clase sin realizar ninguna acci�n adicional.
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
     * Inicializa la f�brica con un tipo espec�fico de forma a gestionar.
     *
     * @param shapeType Tipo de forma que ser� creada (CIRCLE, RECTANGLE, etc.).
     */
    ShapeFactory(ShapeType shapeType);

    /**
     * @brief Crea una nueva forma geom�trica seg�n el tipo indicado.
     *
     * Asigna la forma creada al puntero `m_shape` para su posterior manipulaci�n.
     *
     * @param shapeType El tipo de forma a crear.
     * @return Puntero a la forma creada (`sf::Shape*`).
     */
    sf::Shape* createShape(ShapeType shapeType);

    /**
     * @brief Actualiza el estado de la forma en cada frame.
     *
     * Este m�todo permite manejar animaciones o transiciones de la forma.
     *
     * @param deltaTime Tiempo transcurrido desde el �ltimo frame.
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
     * @brief Establece la posici�n de la forma con coordenadas X e Y.
     *
     * @param x Coordenada X.
     * @param y Coordenada Y.
     */
    void setPosition(float x, float y);

    /**
     * @brief Establece la posici�n de la forma con un vector 2D.
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
     * @brief Establece la rotaci�n de la forma en grados.
     *
     * @param angle �ngulo de rotaci�n.
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
    sf::Shape* m_shape = nullptr;  ///< Puntero a la forma gestionada por esta f�brica.
    ShapeType m_shapeType = ShapeType::EMPTY;  ///< Tipo de forma gestionada.
};
