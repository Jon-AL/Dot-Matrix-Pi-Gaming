/**
 * File contains declaration for concrete `Ball` class. This class implements abstract `Entity` class.
 * 
 * @file Ball.h
 * @co_author https://github.com/Jon-AL
 * @date 30/10/21
 */

#ifndef BALL_H
#define BALL_H

#include "../Entity.h"

class Ball : public Entity {
public:
    Ball(float x, float y, float xVelocity, float yVelocity, float width, float height, const Colour &colour);

    ~Ball() override;

    void update(const std::map<std::string, Entity *> &entities, int boardWidth, int boardHeight) override;

    void onCollision(Entity *collided) override;
};

#endif
