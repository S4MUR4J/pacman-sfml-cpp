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
 * @class Ghost
 *
 * This class stores data and the entire logic of the opponents (so-called ghosts). It changes data about the object, draws it and is responsible for movement.
 */

class Ghost {
    private:
        sf::RectangleShape shape;
        float movementSpeed;
        bool effected;
        sf::Vector2f playerOrigin;
        bool collisionTbl[4];
        int indexX;
        int indexY;
        int nextIndexX;
        int nextIndexY;
        float offset;

        MoveDirection moveDir;
        void initVariables();
        void initShapes(float x, float y);
    public:
        Ghost(const sf::RenderWindow& window, float x, float y);
        virtual ~Ghost();

        virtual sf::RectangleShape getShape();
        
        void changeDir(sf::Keyboard::Key left, sf::Keyboard::Key right,
                        sf::Keyboard::Key top, sf::Keyboard::Key down, float offset);
        sf::Vector2f getPlayerOrigin();
        void nextPosition(MoveDirection moveDir);
        bool isEfected();
        virtual void Effect(bool isOff);
        bool collision(float posX, float posY);
        virtual void updateInput(float x, float y);
        void updateTeleportOnEdge(const sf::RenderTarget *target);
        virtual void update(const sf::RenderTarget * target, float x, float y);
        virtual void render(sf::RenderTarget *target);
};
