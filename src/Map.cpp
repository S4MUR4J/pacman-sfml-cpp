#include "map.h"

/**
*   Function initializes basic object parameters i.e. size, color and position
*
*   @param x x position where we will place the object
*   @param y y position where we will place the object
*
*/
void Map::initShape(float x, float y)
{
    this->shape.setSize(sf::Vector2f(cellSize, cellSize));
    this->shape.setFillColor(sf::Color::Blue);
    this->shape.setPosition(x, y);
}

/**
*   Object constructor responsible for object initialization and shape initialization
*
*   @param window window on which the object is initialized
*   @param x x position where the object will be located
*   @param y y position where the object will be located
*/
Map::Map(const sf::RenderWindow& window, float x, float y)
{
    this->initShape(x, y);
}

Map::~Map()
{

}

/**
*   Function draws individual map objects on the window
*
*   @param target window on which the object should be drawn
*/
void Map::render(sf::RenderWindow & target)
{
    target.draw(this->shape);         
}

