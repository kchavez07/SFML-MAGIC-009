#include "ShapeFactory.h"

/**
 * @brief Implementación del constructor parametrizado.
 *
 * Inicializa la fábrica con un tipo específico de forma.
 */
ShapeFactory::ShapeFactory(ShapeType shapeType)
    : m_shape(nullptr), m_shapeType(shapeType), Component(ComponentType::SHAPE) {}

/**
 * @brief Crea una nueva forma geométrica según el tipo indicado.
 *
 * Asigna la forma creada al puntero `m_shape` y devuelve un puntero a la forma.
 *
 * @param shapeType El tipo de forma a crear.
 * @return Puntero a la forma creada (`sf::Shape*`).
 */
sf::Shape* ShapeFactory::createShape(ShapeType shapeType) {
    m_shapeType = shapeType;

    switch (shapeType) {
    case ShapeType::EMPTY:
        return nullptr;

    case ShapeType::CIRCLE: {
        sf::CircleShape* circle = new sf::CircleShape(10.0f);
        circle->setFillColor(sf::Color::White);
        m_shape = circle;
        return circle;
    }

    case ShapeType::RECTANGLE: {
        sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(100.0f, 50.0f));
        rectangle->setFillColor(sf::Color::White);
        m_shape = rectangle;
        return rectangle;
    }

    case ShapeType::TRIANGLE: {
        sf::CircleShape* triangle = new sf::CircleShape(50.0f, 3);  // Triángulo con 3 puntos.
        triangle->setFillColor(sf::Color::White);
        m_shape = triangle;
        return triangle;
    }

    default:
        return nullptr;
    }
}

/**
 * @brief Actualiza el estado de la forma.
 *
 * Este método se ejecuta en cada frame para realizar cambios dinámicos si es necesario.
 */
void ShapeFactory::update(float deltaTime) {
    // Implementación futura: Añadir lógica de actualización si es necesario.
}

/**
 * @brief Renderiza la forma en la ventana proporcionada.
 *
 * @param window Ventana donde se renderiza la forma.
 */
void ShapeFactory::render(Window& window) {
    if (m_shape != nullptr) {
        window.draw(*m_shape);  // Dibuja la forma en la ventana.
    }
}

/**
 * @brief Establece la posición de la forma con coordenadas X e Y.
 *
 * @param x Coordenada X.
 * @param y Coordenada Y.
 */
void ShapeFactory::setPosition(float x, float y) {
    if (m_shape != nullptr) {
        m_shape->setPosition(x, y);
    }
}

/**
 * @brief Establece la posición de la forma con un vector 2D.
 *
 * @param position Un vector con las coordenadas X e Y.
 */
void ShapeFactory::setPosition(const sf::Vector2f& position) {
    if (m_shape != nullptr) {
        m_shape->setPosition(position);
    }
}

/**
 * @brief Cambia el color de la forma.
 *
 * @param color El nuevo color a aplicar.
 */
void ShapeFactory::setFillColor(const sf::Color& color) {
    if (m_shape != nullptr) {
        m_shape->setFillColor(color);
    }
}

/**
 * @brief Establece la rotación de la forma en grados.
 *
 * @param angle Ángulo de rotación.
 */
void ShapeFactory::setRotation(float angle) {
    if (m_shape != nullptr) {
        m_shape->setRotation(angle);
    }
}

/**
 * @brief Establece la escala de la forma en los ejes X e Y.
 *
 * @param scl Vector con los valores de escala.
 */
void ShapeFactory::setScale(const sf::Vector2f& scl) {
    if (m_shape != nullptr) {
        m_shape->setScale(scl);
    }
}

/**
 * @brief Devuelve un puntero a la forma creada.
 *
 * @return Puntero a la forma (`sf::Shape*`).
 */
sf::Shape* ShapeFactory::getShape() {
    return m_shape;
}
