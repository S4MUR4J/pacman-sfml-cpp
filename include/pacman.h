#pragma once

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "constants.h"

/**
 * @class Pacman
 *
 * Class responsible for storing player information, containing the logic of the player's operation, initializing his parameters and rendering him on the screen
 */
class Pacman{
private:
    sf::CircleShape shape;

    int currentX;
    int currentY;
    int nextPosX;
    int nextPosY;
    unsigned timer;
    bool boosted;
    MoveDirection prevDir;
    float movementSpeed;
    MoveDirection moveDirection;

    void initVariables();
    void initShapes();
public:
    Pacman(float x = 488.f, float y = 728.f);
    virtual ~Pacman();

    const sf::CircleShape& getShape() const;
    bool isBoosted();

    bool canChangeDir();
    void railMoveHelper();
    void updateInput();
    void boostTimer();
    void boost(bool active);
    void updateTeleportOnEdge(const sf::RenderTarget* target);

    void update(const sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};
