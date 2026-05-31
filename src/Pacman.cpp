#include "pacman.h"

/**
 * Function initializes basic variables needed to start working with the object
 */
void Pacman::initVariables() {
    this->movementSpeed = 1.f;
    this->moveDirection = STOP;
    this->boosted = false;
    this->prevDir = STOP;
    this->nextPosX = static_cast<int>(round(this->shape.getPosition().x / cellSize));
    this->nextPosY = static_cast<int>(round(this->shape.getPosition().y / cellSize));
}

/**
 * Initialization of the class object appearance, setting color and radius
 */
void Pacman::initShapes() {
    this->shape.setFillColor(sf::Color::Yellow);
    this->shape.setRadius(16.f);
}

/**
 * Constructor creating player object
 *
 * @param x player's starting position on X axis
 * @param y player's starting position on Y axis
 */
Pacman::Pacman(float x, float y) {
    this->shape.setPosition(x, y);
    this->initVariables();
    this->initShapes();
}

Pacman::~Pacman() {
    
}

const sf::CircleShape & Pacman::getShape() const {
    return this->shape;
}

bool Pacman::isBoosted()
{
    return this->boosted;
}

/**
 * Function gives us information about the possibility of changing direction caused by the position on the grid.
 * If our player is close to a turn
 *
 * @return true player can change direction
 * @return false player cannot change direction
 */
bool Pacman::canChangeDir()
{
    if(abs(this->shape.getPosition().x / cellSize - round(this->shape.getPosition().x / cellSize)) < 0.1f &&
        abs(this->shape.getPosition().y / cellSize - round(this->shape.getPosition().y / cellSize)) < 0.1f) {
        return true;
    }
    return false;
}

/**
 * This function collects information from the keyboard about the user's choice of direction.
 * Similarly, the changed variable helps us in case we cannot turn, then the character returns to the previous direction.
 * Strictly related to the updateInput() function.
 */
void Pacman::railMoveHelper()
{
    bool changed = 0;
    MoveDirection prevDirection = this->moveDirection;

    if(!this->canChangeDir()) {
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) // Left
    {
        this->moveDirection = LEFT;
        changed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // Right
    {
        this->moveDirection = RIGHT;
        changed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) // Down
    {
        this->moveDirection = BOTTOM;
        changed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // Up
    {
        this->moveDirection = TOP;
        changed = true;
    }

    if (changed) {
        changed = false;
        this->prevDir = prevDirection;
    }
}

/**
 * In this function, according to the selected direction, the player is moved on the map.
 * Depending on the direction, we collect his position in a different way to currentX, due to the operation of SFML itself.
 * If there is a wall in front of the player's direction, it stops.
 */
void Pacman::updateInput() {

    if (this->moveDirection == RIGHT || moveDirection == BOTTOM) {
        this->currentX = static_cast<int>((this->shape.getPosition().x - this->shape.getRadius()/2) / cellSize);
        this->currentY = static_cast<int>((this->shape.getPosition().y - this->shape.getRadius()/2) / cellSize);
    } else {
        this->currentX = static_cast<int>((this->shape.getPosition().x + this->shape.getRadius()*2) / cellSize);
        this->currentY = static_cast<int>((this->shape.getPosition().y + this->shape.getRadius()*2) / cellSize); 
    }

    this->nextPosX = this->currentX;
    this->nextPosY = this->currentY;

    if (this->moveDirection == LEFT) { 
        this->nextPosX = this->currentX -1;
        if(map[nextPosY][nextPosX] != 1) {
            this->shape.move(-this->movementSpeed, 0);
        }
        else
            this->moveDirection = this->prevDir;
    }
    if (this->moveDirection == RIGHT) {
        this->nextPosX = this->currentX + 1;
        if(map[nextPosY][nextPosX] != 1) {
            this->shape.move(this->movementSpeed, 0);
        }
        else
            this->moveDirection = this->prevDir;
    }
    if (this->moveDirection == BOTTOM) {
        this->nextPosY = this->currentY + 1;
        if(map[nextPosY][nextPosX] != 1) 
        {
            this->shape.move(0, this->movementSpeed);
        }
        else
            this->moveDirection = this->prevDir;
    }
    if (this->moveDirection == TOP) {
        this->nextPosY = this->currentY - 1;
        if(map[nextPosY][nextPosX] != 1) {
            this->shape.move(0, -this->movementSpeed);
        } 
        else
            this->moveDirection = this->prevDir;
    }   
    
}

/**
 * This function is a timer that decreases the time according to its setting until we reach zero.
 * Strictly related to the boost function, which is called after the time elapses, turning off the boost.
 */
void Pacman::boostTimer()
{
    if(this->timer > 0) {
        this->timer--;
    } else 
        boost(false);
}

/**
 * This function holds the logic for activating and deactivating the boost depending on the parameter.
 * It also sets the timer for its operation.
 *
 * @param active here when called we pass whether we are turning off (false) or turning on boost (true)
 */
void Pacman::boost(bool active)
{
    if (active) {
        this->timer = static_cast<unsigned>(1000.f);
        this->boosted = true;
        this->movementSpeed = 2.f;
    }
    else {
        this->boosted = false;
        this->movementSpeed = 1.f;
    }   
}

/**
 * This function, if we are at the edge of the map on the X axis (we have two such tunnels),
 * moves us to the other side of the tunnel.
 *
 * @param target screen on which the object is moving
 */
void Pacman::updateTeleportOnEdge(const sf::RenderTarget *target) {
    if (this->shape.getGlobalBounds().left <= 0.f) {   
        this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top); 
    }
    if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x + 0.1f) {
        this->shape.setPosition(0.1f, this->shape.getGlobalBounds().top);
    }
}

/**
 * Update of the entire logic for calling functions in the program loop
 *
 * @param target parameter we need to get the screen size
 */
void Pacman::update(const sf::RenderTarget * target) {
    this->boostTimer();
    this->railMoveHelper();
    this->updateInput();
    this->updateTeleportOnEdge(target);
}

/**
 * Function prints this class object on the screen
 *
 * @param target screen on which we print
 */
void Pacman::render(sf::RenderTarget * target) {
    target->draw(this->shape);
}

