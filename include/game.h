#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "pacman.h"
#include "fruit.h"
#include "map.h"
#include "special_fruit.h"
#include "ghost.h"
#include "constants.h"
#include <array>

/**
 * @class Game
 *
 * This class is the game engine that puts together all other classes and interactions between them.
 * It is the only one directly called in main. It is responsible for drawing objects on the screen, updating all objects and interactions between them.
 * It also stores the window, which is created in it and passed as a parameter to other classes.
 */
class Game
{
private:
    sf::VideoMode videoMode;
    sf::RenderWindow* window;
    sf::Event event;

    bool endGame;

    Pacman pacman;

    int points;

    std::vector<Fruit> fruits;
    std::vector<Map> mapTiles;
    std::vector<SpecialFruit> specialFruits;
    std::vector<Ghost> ghosts;
    float spawnTimerMax;
    float spawnTimer;
    int maxFruits;

    void initVariables();
    void initMapTiles();
    void initFruits();
    void initWindow();
    void manageEndGame();
public:
    Game();
    virtual ~Game();

    const bool getEndGame() const;
    const bool executing() const;
    void pollEvents();

    void updateCollision();
    
    void update();
    void render();
};
