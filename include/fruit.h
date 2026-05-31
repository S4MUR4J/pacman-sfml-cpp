#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "constants.h"

/**
 * @class Fruit
 *
 * Class storing information about smaller fruits. Responsible for setting the parameters of this object, updating them and drawing on the screen.
 */

/**
 * This template is a getter for different types of variables
 *
 * @param data variable that we want to pass
 *
 * @return we return the object variable
*/
template <typename T>
T getShapeTemplate(T data) {
    T result = data;
    return result;
}

class Fruit {
private:
    sf::RectangleShape shape;

    void initShape(const sf::RenderWindow& window, float x, float y);
public:   
    Fruit(const sf::RenderWindow& window, float x, float y);
    virtual ~Fruit();

    const sf::RectangleShape getShape() const;
    
    virtual void render(sf::RenderTarget& target);
};
