/**
 * File contains definition of abstract `Renderer` class.
 *
 * @file Renderer.cpp
 * @co_author https://github.com/Jon-AL
 * @date 28/10/21
 */

#include <iostream>
#include "Renderer.h"

/**
 * @brief Constructor for when no matrix is provided.
 *
 * Constructs new instance with the provided width and height, with the previous matrix being initialised as an empty 
 * vector.
 * 
 * @param width the width of the matrix
 * @param height the height of the matrix
 */
Renderer::Renderer(int width, int height) {
    this->width = width;
    this->height = height;
    this->previousMatrix = {};
}

/**
 * @brief Constructor for when a pre-defined matrix is provided to display.
 *
 * Constructs new instance with the width and height of the provided matrix, with the previous matrix set as the matrix 
 * provided.
 * 
 * @param matrix the 2D vector to be used to construct renderer (and to be displayed)
 */
Renderer::Renderer(const std::vector<std::vector<std::pair<std::string, Colour>>> &matrix) {
    this->width = matrix[0].size();
    this->height = matrix.size();
    this->previousMatrix = matrix;
}

/**
 * @brief Default destructor.
 * 
 * No memory is allocated.
 */
Renderer::~Renderer() = default;

/**
 * @brief Getter for the width of the matrix.
 *
 * @return the width of the matrix
 */
int Renderer::getWidth() const {
    return width;
}

/**
 * @brief Getter for the height of the matrix.
 *
 * @return the height of the matrix
 */
int Renderer::getHeight() const {
    return height;
}
