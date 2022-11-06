/**
 * File contains declaration for concrete `Paddle` class. This class implements abstract `Entity` class.
 * 
 * @file Paddle.h
 * @co_author https://github.com/Jon-AL
 * @date 08/11/21
 */

#ifndef PADDLE_H
#define PADDLE_H

#include "../Entity.h"

/**
 * @brief Declaration for concrete `Paddle` class.
 *
 * Class provides implementation of entity `Paddle` which inherits from abstract superclass `Entity`.
 */
class Paddle : public Entity {
public:
    Paddle(float x, float y, float xVelocity, float yVelocity, float width, float height, const Colour &colour, bool isAI, int difficulty);

    ~Paddle() override;

    void update(const std::map<std::string, Entity *> &entity, int boardWidth, int boardHeight) override;

    void onCollision(Entity *collided) override;
private:
    bool isAI;
    int difficulty;
    int tickCounter;
};

#endif