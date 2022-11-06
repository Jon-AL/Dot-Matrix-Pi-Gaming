/**
 * File contains concrete definition of `Paddle` subclass.
 *
 * @file Paddle.cpp
 * @co_author https://github.com/Jon-AL
 * @date 08/11/21
 */

#include "Paddle.h"

#define CHAR "\u2588"

/**
 * @brief Basic constructor.
 *
 * The constructor for abstract superclass `Entity` is called with the provided parameters. There is no additional
 * implementation.
 *
 * @param x the initial x coordinate of the paddle
 * @param y the initial y coordinate of the paddle
 * @param xVelocity the initial x velocity of the paddle
 * @param yVelocity the initial y velocity of the paddle
 * @param width the initial width of the paddle
 * @param height the initial height of the paddle
 * @param colour the colour of the paddle (if applicable)
 */
Paddle::Paddle(float x, float y, float xVelocity, float yVelocity, float width, float height, const Colour &colour, bool isAI, int difficulty)
        : Entity(x, y, xVelocity, yVelocity, width, height, CHAR, colour) {
            this->isAI = isAI;
            this->difficulty = ((3 - difficulty) * 4);
        }

/**
* @brief Default destructor.
*
* No memory is allocated.
*/
Paddle::~Paddle() = default;

/**
 * @brief Updates the position of the paddle given other entities in the current instance of `Game`.
 *
 * @param entity the entities currently on the game board
 * @param boardWidth the width of the board
 * @param boardHeight the height of the board
 */
void Paddle::update(const std::map<std::string, Entity *> &entity, int boardWidth, int boardHeight) {
    if(isAI){
        if(difficulty==0 || tickCounter % difficulty == 0){
            for(auto const &ent:entity){
                if(ent.first == "ball") {
                    if(ent.second->getX() < x && ent.second->getXVelocity() > 0 || ent.second->getX() > x && ent.second->getXVelocity() < 0){
                        if(y < ent.second->getY() && (y+(height/2)) < (boardHeight-1)){
                            yVelocity=1;
                        }else if (y > ent.second->getY() && (y-(height/2))>0){
                            yVelocity=-1;
                        }else{
                            yVelocity=0;
                        }
                    }else{
                        yVelocity = 0;
                    }
                }
            }
        }
        tickCounter++;
    }

    if (yVelocity > 0) {
        if (y + (height / 2) + yVelocity > boardHeight) {
            y = boardHeight - (height / 2) - 1;
        } else {
            y = y + yVelocity;
        }
    } else if (yVelocity < 0) {
        if (y - height / 2 + yVelocity < 0) {
            y = y + (height / 2);
        } else {
            y = y + yVelocity;
        }
    } else {
        yVelocity = 0;
    }
}


/**
 * @brief Handles the paddle colliding with another entity.
 *
 * @param collided the entity the paddle collided with
 */
void Paddle::onCollision(Entity *collided) {}
