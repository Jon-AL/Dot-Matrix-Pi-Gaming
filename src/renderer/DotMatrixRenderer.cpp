/**
 * File contains concrete definition of `DotMatrixRenderer` subclass.
 * 
 * @file DotMatrixRenderer.cpp
 * @co_author https://github.com/Jon-AL
 * @date 05/11/21
 */

#include <iostream>
#include "DotMatrixRenderer.h"

/**
 * @brief Constructor for when no matrix is provided.
 * 
 * The constructor for abstract superclass `Renderer` is called with the provided parameters. There is no additional
 * implementation.
 *
 * @param width the width of the matrix
 * @param height the height of the matrix
 */
DotMatrixRenderer::DotMatrixRenderer(int width, int height) : Renderer(width, height) {}

/**
 * @brief Constructor for when a pre-defined matrix is provided to display.
 *
 * The constructor for abstract superclass `Renderer` is called with the provided parameters. There is no additional
 * implementation.
 * 
 * @param matrix the 2D vector to be used to construct renderer (and to be displayed)
 */
DotMatrixRenderer::DotMatrixRenderer(const std::vector<std::vector<std::pair<std::string, Colour>>> &matrix)
        : Renderer(matrix) {}

/**
 * @brief Default destructor.
 * 
 * No memory is allocated.
 */
DotMatrixRenderer::~DotMatrixRenderer() = default;

/**
 * @brief Stub; method not yet implemented.
 * 
 * Writes the textual representation of the provided matrix to the command line, given a 2D vector.
 *
 * @param matrix the matrix to be drawn
 */
void DotMatrixRenderer::draw(const std::vector<std::vector<std::pair<std::string, Colour>>> &matrix) {
    std::cerr << "No implementation provided for `DotMatrixRenderer::draw(const std::vector<std::vector<std::string>>)`"
              << std::endl;
    exit(0);
}

/**
 * @brief Stub; method not yet implemented.
 * 
 * Makes a change to the previously displayed matrix array and writes the textual representation of this new matrix to
 * the command line, given the position and new pair of character and colour.
 *
 * @param x the x-coordinate of the position in the matrix to be updated
 * @param y the y-coordinate of the position in the matrix to be updated
 * @param state the new pair of character and colour at the position to be updated
 */
void DotMatrixRenderer::draw(int x, int y, std::pair<std::string, Colour> state) {
    std::cerr << "No implementation provided for `DotMatrixRenderer::draw(int, int, std::string)`" << std::endl;
    exit(0);
}

/**
 * @brief Displays in-game menu. Stub; method not yet implemented.
 *
 * With a provided menu text string and a vector containing all of the menu options, the menu is written to the
 * dot-matrix. Input is not handled here.
 *
 * @param menuText the text displayed at the top of the menu (e.g., the question)
 * @param options vector containing list of options the user may select
 */
void DotMatrixRenderer::displayMenu(std::string menuText, std::vector<std::string> options) {
    std::cerr
            << "No implementation provided for `DotMatrixRenderer::displayMenu(std::string, std::vector<std::string>)`"
            << std::endl;
    exit(0);
}

/**
 * @brief Prints a message to the console. Stub; method not implemented yet.
 *
 * The console reset can be disabled to allow messages to be displayed one after the other where applicable.
 *
 * @param message the message to be reset
 * @param reset whether the console should be reset
 */
void DotMatrixRenderer::displayMessage(std::string message, bool reset) {
    std::cerr << "No implementation provided for `DotMatrixRenderer::displayMessage(std::string, bool)`" << std::endl;
    exit(0);
}
