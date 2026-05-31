#include "special_fruit.h"
/**
 * Function responsible for initializing basic special fruit parameters such as color, diameter, and position
 *
 * @param window window on which the special fruit will be
 * @param x special fruit position on X axis
 * @param y special fruit position on Y axis
 */
void SpecialFruit::initShape(const sf::RenderWindow &window, float x, float y)
{
    this->shape.setFillColor(sf::Color::White);
    this->shape.setRadius(12.f);
    this->shape.setPosition(sf::Vector2f(x - this->shape.getRadius()/2, y - this->shape.getRadius()/2));
    
}

/**
 * Special fruit object constructor, calling initialization of basic object parameters
 *
 * @param window window on which the special fruit will be drawn
 * @param x special fruit position on X axis
 * @param y special fruit position on Y axis
 */
SpecialFruit::SpecialFruit(const sf::RenderWindow &window, float x, float y) : Fruit(window, x, y)
{
    this->initShape(window, x, y);
}

SpecialFruit::~SpecialFruit()
{
}

const sf::CircleShape SpecialFruit::getShape() const
{
    sf::CircleShape result = getShapeTemplate<sf::CircleShape>(this->shape);
    return result;
}

/**
 * Function responsible for drawing the special fruit on the screen
 *
 * @param target screen on which the special fruit will be rendered
 */
void SpecialFruit::render(sf::RenderTarget &target) {
    target.draw(this->shape);
}
