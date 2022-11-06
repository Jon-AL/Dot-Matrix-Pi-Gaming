/**
 * File contains declaration for abstract `Entity` class.
 *
 * @file Entity.h
 * @co_author https://github.com/Jon-AL
 * @date 30/10/21
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <map>
#include "Colour.h"
#include <cmath>

/**
 * @brief Declaration for abstract `Entity` class.
 *
 * Class provides declarations required for concrete subclass implementation. Definitions are provided for constructors,
 * a destructor and basic getter/setter methods.
 */
class Entity {
protected:
    float x;
    float y;
    float xVelocity;
    float yVelocity;
    float width;
    float height;
    std::string representation;
    Colour colour;

public:
    Entity(float x, float y, float xVelocity, float yVelocity, float width, float height, std::string representation,
           const Colour &colour);

    Entity(const Entity &entity);

    virtual ~Entity() = 0;

    virtual void update(const std::map<std::string, Entity *> &entities, int boardWidth, int boardHeight) = 0;

    float getX() const;

    float getY() const;

    float getXVelocity() const;

    float getYVelocity() const;

    float getWidth() const;

    float getHeight() const;

    std::string getRepresentation() const;

    std::pair<std::string, Colour> getDisplayPair() const;

    Colour getColour() const;

    void setX(float x);

    void setY(float y);

    void setXVelocity(float xVelocity);

    void setYVelocity(float yVelocity);

    void setWidth(float width);

    void setHeight(float height);

    void setRepresentation(std::string representation);

    void setColour(const Colour &colour);

    virtual void onCollision(Entity *collided) = 0;
};

#endif
