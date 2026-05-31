#include "ghost.h"

/**
 * Function responsible for initializing basic variables needed to start working with the object
 */
void Ghost::initVariables() {
    this->movementSpeed = 20.f;
    this->moveDir = STOP;
    this->effected = false;
    this->indexX = floor(getPlayerOrigin().x / cellSize);
    this->indexY = floor(getPlayerOrigin().y / cellSize);
    this->nextIndexX = this->indexX;
    this->nextIndexY = this->indexY;
    this->offset = this->shape.getSize().x/2;
}

/**
 * Function responsible for initializing object appearance, setting position, color and size
 *
 * @param x ghost position on X axis
 * @param y ghost position on Y axis
 */
void Ghost::initShapes(float x, float y) {
    this->shape.setFillColor(sf::Color::Magenta);
    this->shape.setSize(sf::Vector2f(24.f, 24.f));
    this->shape.setPosition(sf::Vector2f(x, y));
}


/**
 * Constructor creating the ghost class
 *
 * @param window window on which the ghost will be created
 * @param x ghost position on X axis
 * @param y ghost position on Y axis
 */
Ghost::Ghost(const sf::RenderWindow& window, float x, float y)
{
    this->initShapes(x, y);
    this->initVariables();
}

Ghost::~Ghost()
{

}

sf::RectangleShape Ghost::getShape()
{
    return this->shape;
}

/**
 * This function is a getter for the ghost's fear property, which is the state when the player eats a special fruit
 *
 * @return true ghost is frightened
 * @return false ghost is not frightened
 */
bool Ghost::isEfected()
{
    return this->effected;
}

/**
 * Function calculates the global position of the ghost according to its center and returns its value
 *
 * @return sf::Vector2f vector of the center position of the object
*/
sf::Vector2f Ghost::getPlayerOrigin()
{
    float x = this->shape.getPosition().x + cellSize/4;
    float y = this->shape.getPosition().y + cellSize/4;
    sf::Vector2f origin(x, y);
    return origin;
}

/**
 * Function checks the next position on the grid and sets it to a variable for further checks in the movement logic
 *
 * @param movDir current direction of movement
*/
void Ghost::nextPosition(MoveDirection moveDir) {

    switch(moveDir) {
        case LEFT:
            this->nextIndexX = this->indexX;
            this->nextIndexX--;
            this->nextIndexY = this->indexY;
            break;
        case RIGHT:
            this->nextIndexX = this->indexX;
            this->nextIndexX++;
            this->nextIndexY = this->indexY;
            break;
        case TOP:
            this->nextIndexY = this->indexY;
            this->nextIndexY--;
            this->nextIndexX = this->indexX;
            break;
        case BOTTOM:
            this->nextIndexY = this->indexY;
            this->nextIndexY++;
            this->nextIndexX = this->indexX;
            break;
        default:
            this->nextIndexX = this->indexX;
            this->nextIndexY = this->indexY;
            break;
    }
}

/**
 * Function responsible for changing the direction of movement depending on the keyboard input
 *
 * @param left button to move left
 * @param right button to move right
 * @param down button to move down
 * @param top button to move up
 * @param offset character offset
*/

void Ghost::changeDir(sf::Keyboard::Key left, sf::Keyboard::Key right,
                         sf::Keyboard::Key top, sf::Keyboard::Key down, float offset)
{
    if (sf::Keyboard::isKeyPressed(left)) {
        this->shape.setPosition(this->indexX * cellSize + offset, this->indexY * cellSize + offset);
        this->moveDir = LEFT;
    } 
    else if (sf::Keyboard::isKeyPressed(right)) {
        this->shape.setPosition(this->indexX * cellSize + offset, this->indexY * cellSize + offset);
        this->moveDir = RIGHT;
    }
    else if (sf::Keyboard::isKeyPressed(top)) {
        this->shape.setPosition(this->indexX * cellSize + offset, this->indexY * cellSize + offset);
        this->moveDir = TOP;
    }
    else if (sf::Keyboard::isKeyPressed(down)) {
        this->shape.setPosition(this->indexX * cellSize + offset, this->indexY * cellSize + offset);
        this->moveDir = BOTTOM;
    }
}

/**
 * This function is responsible for the logic of being in a frightened state and does not affect the ability to destroy the player and ghost speed
 *
 * @param isOff parameter used to activate and deactivate the frightened effect
 */
void Ghost::Effect(bool isOff)
{
    if(!isOff) {
        this->effected = true;
        this->movementSpeed = 0.55f;
    }      
    else {
        this->effected = false;
        this->movementSpeed = 0.1f;
    }

}

/**
 * If the ghost is at the edge of the screen on the X axis, it is moved to the other side of the screen
 *
 * @param target screen from which we get its size
 */
void Ghost::updateTeleportOnEdge(const sf::RenderTarget *target) {
    if (this->nextIndexX < 0 && this->indexX == 0) {   
        this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top); 
    }
    if (this->nextIndexX > 20 && this->indexX == 20) {
        this->shape.setPosition(0.1f, this->shape.getGlobalBounds().top);
    }
}

/**
 * Function checks neighboring grid fields to find a wall collision
 *
 * @param posX ghost position on X axis
 * @param posY ghost position on Y axis
 * @return true wall exists for the given direction of movement
 * @return false wall does not exist for the given direction of movement
*/
bool Ghost::collision(float posX, float posY)
{
    bool result = false;

    int gridX = static_cast<int>(floor(posX / cellSize));
    int gridY = static_cast<int>(floor(posY / cellSize));

    switch(this->moveDir) {
        case LEFT:
            if(map[this->nextIndexY][this->nextIndexX] == 1 && 
            abs(this->getPlayerOrigin().x - this->indexX * cellSize - cellSize/2) < 0.5f)
            {
                return true;
            }
            break;
        case RIGHT:
            if(map[this->nextIndexY][this->nextIndexX] == 1 && 
                abs(this->getPlayerOrigin().x - this->indexX * cellSize - cellSize/2) < 0.5f)
            {
                return true;
            }
            break;
        case TOP:
            if(map[this->nextIndexY][this->nextIndexX] == 1 &&
                abs(this->getPlayerOrigin().y - this->indexY * cellSize - cellSize/2) < 0.5f)
            {
                return true;
            }
            break;
        case BOTTOM:
            if(map[this->nextIndexY][this->nextIndexX] == 1 &&
            abs(this->getPlayerOrigin().y - this->indexY * cellSize - cellSize/2) < 0.5f)
            {
                return true;
            }
            break;
    };

    return result;
}

/**
 * This function contains the logic for the ghost's movement, which moves on the grid and can only move where the value is not 1.
 *
 * @param x current player position on X axis
 * @param y current player position on Y axis
 */
void Ghost::updateInput(float x, float y)
{
    sf::Vector2f position = this->getPlayerOrigin();
    float ghostX = position.x;
    float ghostY = position.y;
    this->indexX = static_cast<int>(floor((position.x)/ cellSize));
    this->indexY = static_cast<int>(floor((position.y)/ cellSize));

    changeDir(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::S, this->offset);
    for (int i = 0; i < 4; i ++) {
        if(i == 0)
            this->collisionTbl[0] = collision(ghostX - movementSpeed, ghostY); // Left
        if(i == 1)
            this->collisionTbl[1] = collision(ghostX + movementSpeed, ghostY); // Right
        if(i == 2)
            this->collisionTbl[2] = collision(ghostX, ghostY - movementSpeed); // Top
        if(i == 3)
            this->collisionTbl[3] = collision(ghostX, ghostY + movementSpeed); // Bottom
    }

    if (!this->effected) {
        return;
    }

    if (this->moveDir == LEFT && this->collisionTbl[0] != true) {
        this->shape.move(-this->movementSpeed, 0.f);
    } 
    else if (this->moveDir == RIGHT && this->collisionTbl[1] != true) {
        this->shape.move(this->movementSpeed, 0.f);
    }
    else if (this->moveDir == TOP && this->collisionTbl[2] != true) {
        this->shape.move(0.f, -this->movementSpeed);
    }
    else if (this->moveDir == BOTTOM && this->collisionTbl[3] != true) {
        this->shape.move(0.f, this->movementSpeed);
    } 
    else {
        this->shape.setPosition(this->indexX * cellSize + 12.f, this->indexY * cellSize + 12.f);
    }
}

/**
 * Function for calling ghost logic in the game engine
 *
 * @param target screen on which the ghost is located
 * @param x current ghost position on X axis
 * @param y current ghost position on Y axis
 */
void Ghost::update(const sf::RenderTarget * target, float x, float y)
{
    this->updateTeleportOnEdge(target);
    this->nextPosition(this->moveDir);
    this->updateInput(x, y);
}

/**
 * Function responsible for drawing the ghost on the screen
 *
 * @param target screen on which the ghost object is drawn
 */
void Ghost::render(sf::RenderTarget * target)
{
    target->draw(this->shape);
}

