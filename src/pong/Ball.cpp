/**
 * File contains concrete definition of `Ball` subclass with appropriate static helper functions.
 *
 * @file Ball.cpp
 * @co_author https://github.com/Jon-AL
 * @date 30/10/21
 */

#include "Ball.h"

#define CHAR "\u2B24"
#define PI 3.14159265

/**
 * @brief Basic constructor.
 *
 * The constructor for abstract superclass `Entity` is called with the provided parameters. There is no additional
 * implementation.
 *
 * @param x the initial x coordinate of the ball
 * @param y the initial y coordinate of the ball
 * @param xVelocity the initial x velocity of the ball
 * @param yVelocity the initial y velocity of the ball
 * @param width the initial width of the ball
 * @param height the initial height of the ball
 * @param colour the colour of the ball (if applicable)
 */
Ball::Ball(float x, float y, float xVelocity, float yVelocity, float width, float height, const Colour &colour)
        : Entity(x, y, xVelocity, yVelocity, width, height, CHAR, colour) {}

/**
* @brief Default destructor.
*
* No memory is allocated.
*/
Ball::~Ball() = default;

/**
 * @brief Updates the position of the ball given other entities in the current instance of `Game`.
 *
 * The position of the ball is updated, with pre and post-collision checks taking place to ensure collisions occur
 * correctly.
 *
 * @param entities the entities currently on the game board
 * @param boardWidth the width of the board
 * @param boardHeight the height of the board
 */
void Ball::update(const std::map<std::string, Entity *> &entities, int boardWidth, int boardHeight) {
    // Pre-collision checking of the position after moving
    float nextPositionX = x + xVelocity;
    float nextPositionY = y + yVelocity;

    // Checking the collision of the ball against the walls of the game board.
    if (nextPositionY < 0 || nextPositionY >= boardHeight) {
        yVelocity = -yVelocity;
    }

    // Checks what the entity is colliding with, and reacts accordingly.

    int interpolate = 20;

    for (auto const &ent: entities) {
        if (ent.first == "ball") {
            continue;
        }

        float xl2 = ent.second->getX() - (ent.second->getWidth() / 2);
        float xr2 = ent.second->getX() + (ent.second->getWidth() / 2);
        float yt2 = ent.second->getY() + (ent.second->getHeight() / 2);
        float yb2 = ent.second->getY() - (ent.second->getHeight() / 2);

        if(interpolate > 0){
            for(int i = 0; i <= interpolate; i++){
                float xl1 = (nextPositionX - (width / 2));
                float xr1 = (nextPositionX + (width / 2));
                float yt1 = (nextPositionY - (height / 2));
                float yb1 = (nextPositionY + (height / 2));
                if(xVelocity >= 0){
                    xl1 -= ((xVelocity / interpolate) * i);
                    xr1 -= ((xVelocity / interpolate) * i);
                    yt1 -= ((yVelocity / interpolate) * i);
                    yb1 -= ((yVelocity / interpolate) * i);
                }else{
                    xl1 += ((xVelocity / interpolate) * i);
                    xr1 += ((xVelocity / interpolate) * i);
                    yt1 += ((yVelocity / interpolate) * i);
                    yb1 += ((yVelocity / interpolate) * i);
                }

                if((xl1 >= xl2 && xl1 <= xr2) || (xr1 <= xr2 && xr1 >= xl2)){
                    if((yt1 <= yt2 && yt1 >= yb2) || (yt1 >= yt2 && yb1 <= yb2)){
                        onCollision(ent.second);
                        break;
                    }
                }
            }
        }
    }

    // Post-collision checking of the position after moving.
    nextPositionX = x + xVelocity;
    nextPositionY = y + yVelocity;
    x = nextPositionX;
    y = nextPositionY;
}

/**
 * @brief Handles the ball colliding with another entity.
 *
 * Performs changes required to the ball state when it collides with a given entity.
 *
 * @param collided the entity the ball collided with
 */
void Ball::onCollision(Entity *collided) {
    if (collided != nullptr) {
        float nextPositionY = y + yVelocity;

        float rad = 90.0f * (PI/180.0f);

        float difference = (((nextPositionY - collided->getY()) / (collided->getHeight() / 2.0f)) * 45.0f) * (PI/180.0f);
        rad += difference;
        
        xVelocity = xVelocity < 0 ? std::sin(rad) : -std::sin(rad);
        yVelocity = yVelocity < 0 ? std::cos(rad) : -std::cos(rad);
    }
}
