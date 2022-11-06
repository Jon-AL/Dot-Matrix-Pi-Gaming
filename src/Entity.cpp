/**
 * File contains definition of abstract `Entity` class.
 *
 * @file Entity.cpp
 * @co_author https://github.com/Jon-AL
 * @date 30/10/21
 */

#include "Entity.h"

#include <utility>

/**
 * @brief Constructor for a new `Entity` of the type of a concrete subclass.
 *
 * Constructs a new instance of a concrete subclass of `Entity` with the provided x and y coordinates, x and y
 * velocities, width, height and colour.
 *
 * @param x the x coordinate of the entity
 * @param y the y coordinate of the entity
 * @param xVelocity the x velocity of the entity
 * @param yVelocity the y velocity of the entity
 * @param width the width of the entity
 * @param height the height of the entity
 * @param representation the character representation to be used for the entity
 * @param colour the colour of the entity (where applicable)
 */
Entity::Entity(float x, float y, float xVelocity, float yVelocity, float width, float height, std::string representation,
               const Colour &colour) {
    this->x = x;
    this->y = y;
    this->xVelocity = xVelocity;
    this->yVelocity = yVelocity;
    this->width = width;
    this->height = height;
    this->representation = std::move(representation);
    this->colour = colour;
}

/**
 * @brief Copy-constructor to create new `Entity` given an existing instance.
 *
 * Copies a previously declared instance of a concrete subclass of `Entity`.
 *
 * @param entity the previously instantiated entity to be copied
 */
Entity::Entity(const Entity &entity) {
    this->x = entity.x;
    this->y = entity.y;
    this->xVelocity = entity.xVelocity;
    this->yVelocity = entity.yVelocity;
    this->width = entity.width;
    this->height = entity.height;
    this->representation = entity.representation;
    this->colour = entity.colour;
}

/**
 * @brief Default destructor.
 *
 * No memory is allocated.
 */
Entity::~Entity() = default;

/**
 * @brief Getter for the x coordinate of the entity.
 *
 * @return the x coordinate of the entity
 */
float Entity::getX() const {
    return x;
}

/**
 * @brief Getter for the y coordinate of the entity.
 *
 * @return the y coordinate of the entity
 */
float Entity::getY() const {
    return y;
}

/**
 * @brief Getter for the x velocity of the entity.
 *
 * @return the x velocity of the entity
 */
float Entity::getXVelocity() const {
    return xVelocity;
}

/**
 * @brief Getter for the y velocity of the entity.
 *
 * @return the y velocity of the entity
 */
float Entity::getYVelocity() const {
    return yVelocity;
}

/**
 * @brief Getter for the width of the entity.
 *
 * @return the width of the entity
 */
float Entity::getWidth() const {
    return width;
}

/**
 * @brief Getter for the height of the entity.
 *
 * @return the height of the entity
 */
float Entity::getHeight() const {
    return height;
}

/**
 * @brief Getter for the character representation of the entity.
 *
 * @return the string representation of the entity
 */
std::string Entity::getRepresentation() const {
    return representation;
}

/**
 * @brief Getter for the character Colour pair used to display the entity.
 *
 * @return the character Colour pair of the entity
 */
std::pair<std::string, Colour> Entity::getDisplayPair() const {
    return std::make_pair(representation, colour);
}

/**
 * Getter for the colour of the entity.
 *
 * @return the colour of the entity
 */
Colour Entity::getColour() const {
    return colour;
}

/**
 * @brief Setter for the x coordinate of the entity.
 *
 * @param x the new x coordinate
 */
void Entity::setX(float x) {
    this->x = x;
}

/**
 * @brief Setter for the y coordinate of the entity.
 *
 * @param y the new y coordinate
 */
void Entity::setY(float y) {
    this->y = y;
}

/**
 * @brief Setter for the x velocity of the entity.
 *
 * @param xVelocity the new x velocity
 */
void Entity::setXVelocity(float xVelocity) {
    this->xVelocity = xVelocity;
}

/**
 * Setter for the y velocity of the entity.
 *
 * @param yVelocity the new y velocity
 */
void Entity::setYVelocity(float yVelocity) {
    this->yVelocity = yVelocity;
}

/**
 * @brief Setter for the width of the entity.
 *
 * @param width thew new width
 */
void Entity::setWidth(float width) {
    this->width = width;
}

/**
 * @brief Setter for the height of the entity.
 *
 * @param height the new height
 */
void Entity::setHeight(float height) {
    this->height = height;
}

/**
 * @brief Setter for the character representation of the entity.
 *
 * @param representation the new string representation
 */
void Entity::setRepresentation(std::string representation) {
    this->representation = representation;
}

/**
 * @brief Setter for the colour of the entity.
 *
 * @param colour the new colour object
 */
void Entity::setColour(const Colour &colour) {
    this->colour = colour;
}
