#pragma once
#include "fruit.h"

/**
 * @class SpecialFruit
 *
 * Class storing information about special fruits. Responsible for setting the parameters of this object, updating them and drawing on the screen.
 */
class SpecialFruit : public Fruit {
private:
    sf::CircleShape shape;
    
    void initShape(const sf::RenderWindow& window, float x, float y);
public:
    SpecialFruit(const sf::RenderWindow& window, float x, float y);
    virtual ~SpecialFruit();

    const sf::CircleShape getShape() const;

    void render(sf::RenderTarget& target) override;
};
