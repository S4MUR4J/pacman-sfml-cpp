#include "fruit.h"

/**
 * Function responsible for initializing basic fruit parameters such as color, diameter, and position
 *
 * @param window window on which the fruit will be
 * @param x fruit position on X axis
 * @param y fruit position on Y axis
 */
void Fruit::initShape(const sf::RenderWindow& window, float x, float y) {
    this->shape.setFillColor(sf::Color::White);
    this->shape.setSize(sf::Vector2f(10.f, 10.f));
    this->shape.setPosition(sf::Vector2f(x, y));
}

/**
 * Fruit object constructor, calling initialization of basic object parameters
 *
 * @param window window on which the fruit will be drawn
 * @param x fruit position on X axis
 * @param y fruit position on Y axis
 */
Fruit::Fruit(const sf::RenderWindow& window, float x, float y) {
    this->initShape(window, x, y);
}

Fruit::~Fruit() {
}

const sf::RectangleShape Fruit::getShape() const {
    sf::RectangleShape result = getShapeTemplate<sf::RectangleShape>(this->shape);
    return result;
}

/**
 * Function responsible for drawing the fruit on the screen
 *
 * @param target screen on which the fruit will be rendered
 */
void Fruit::render(sf::RenderTarget &target) {
    target.draw(this->shape);
}

