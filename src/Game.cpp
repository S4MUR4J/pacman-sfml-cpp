#include "game.h"

/**
 * Initialization of basic game variables such as game state and score
 */
void Game::initVariables() {
    this->endGame = false;
    this->points = 0;
}

/**
 * Function initializing the array holding all map blocks, based on the map sketch
 */
void Game::initMapTiles()
{
    for(int i = 0; i < mapHeight; i++) {
        for(int j = 0; j < mapWidth; j++) {
            if (map[j][i] == 1)
                this->mapTiles.push_back(Map(*this->window, i * cellSize, j * cellSize));
        }
    }
}

/**
 * Function initializing the array holding all fruits and special fruits, based on the map sketch
 */
void Game::initFruits() {
    for(int i = 0; i < mapHeight; i++) {
        for(int j = 0; j < mapWidth; j++) {
            if (map[j][i] == 0)
                this->fruits.push_back(Fruit(*this->window, i * cellSize + 20.f, j * cellSize + 20.f));
            if (map[j][i] == 3)
                this->specialFruits.push_back(SpecialFruit(*this->window, i * cellSize + 20.f, j * cellSize + 20.f));
            if(map[j][i] == 7)
                this->ghosts.push_back(Ghost(*this->window, i * cellSize + 14.f, j * cellSize + 14.f));
        }
    }
}

/**
 * Initialization of the game window, setting its size, frame rate limit and buttons such as minimize and close.
 */
void Game::initWindow() {
    this->videoMode.width = mapWidth * cellSize;
    this->videoMode.height = mapHeight * cellSize;
    this->window = new sf::RenderWindow(this->videoMode, "Pac-Man", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(165);
}

/**
 * This function contains the logic for ending the game. It happens when we eat all fruits and all special fruits, then we consider it a game win.
 */
void Game::manageEndGame()
{
    if(this->fruits.empty() && this->specialFruits.empty()) {
        this->endGame = true;
    }
    for (size_t i = 0; i < this->ghosts.size(); i++) {
        if (this->pacman.getShape().getGlobalBounds().intersects(this->ghosts[i].getShape().getGlobalBounds())) {
            if (!this->pacman.isBoosted())
                this->endGame = true;
        }
    }
}

/**
 * Constructor of the game engine class initializes variables, map construction, fruit placement and window setup
 */
Game::Game() {
    this->initVariables();
    this->initMapTiles();
    this->initFruits();
    this->initWindow();
}

/**
 * Destructor of the game engine class deletes the window and closes the application
 */
Game::~Game() {
    delete this->window;
}

/**
 * This function is a getter for information about the end of the game
 *
 * @return true game has ended
 * @return false game has not ended
 */
const bool Game::getEndGame() const {
    return this->endGame;
}

/**
 * Function provides information about the game state, whether it is running or has just ended by losing or closing the window
 *
 * @return true game is running
 * @return false game has ended
 */
const bool Game::executing() const {
    return this->window->isOpen() && this->endGame == false;
}

/**
 * Function checking events to close the window. If we click ESC or the game is finished, we close the program and window.
 */
void Game::pollEvents() {
    while (this->window->pollEvent(this->event))
    {
        switch(this->event.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(this->event.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

/**
 * In this function we check collisions between game objects such as fruits, special fruits and the player.
 * In the case of fruits, it allows us to pick them up and increase the score.
 */

void Game::updateCollision() {
    for (size_t i = 0; i < this->fruits.size(); i++) {
        if (this->pacman.getShape().getGlobalBounds().intersects(this->fruits[i].getShape().getGlobalBounds())) {
            this->points++;
            this->fruits.erase(this->fruits.begin() + i);
        }
    }
    for (size_t i = 0; i < this->specialFruits.size(); i++) {
        if (this->pacman.getShape().getGlobalBounds().intersects(this->specialFruits[i].getShape().getGlobalBounds())) {
            this->pacman.boost(true);
            this->points++;
            this->specialFruits.erase(this->specialFruits.begin() + i);
        }
    }
}

/**
 * Update of all objects and events in our program, also currently changing the ghost's frightened state. We also call the entire engine logic here.
 */
void Game::update() {
    this->pollEvents();

    if (this->endGame == false) {
        this->pacman.update(this->window);
        for(size_t i = 0; i < this->ghosts.size(); i++) {
            this->ghosts[i].update(this->window, 
                                this->ghosts[i].getShape().getPosition().x + ghosts[i].getShape().getSize().x/2,
                                this->ghosts[i].getShape().getPosition().y + ghosts[i].getShape().getSize().y/2);
            if(this->pacman.isBoosted())
                this->ghosts[i].Effect(true);
            if(!this->pacman.isBoosted())
                this->ghosts[i].Effect(false);
        }
        this->updateCollision();
        this->manageEndGame();
    }
}

/**
 * Function in which we draw all class objects on the screen. We first clear the screen, print the content and display it. This happens every frame.
 */
void Game::render() {
    this->window->clear();

    for (auto i : this->mapTiles) {
        i.render(*this->window);
    }
    for (auto i : this->fruits) {        
        i.render(*this->window);
    }

    for (auto i : this->specialFruits) {        
        i.render(*this->window);
    }

    for (auto i : this->ghosts) {        
        i.render(this->window);
    }
    
    this->pacman.render(this->window);

    this->window->display();
}


