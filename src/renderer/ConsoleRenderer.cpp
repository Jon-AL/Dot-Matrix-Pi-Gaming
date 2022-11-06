/**
 * File contains concrete definition of `ConsoleRenderer` subclass with appropriate static helper functions.
 * 
 * @file ConsoleRenderer.cpp
 * @co_author https://github.com/Jon-AL
 * @date 05/11/21
 */

#include <iostream>
#include "ConsoleRenderer.h"

#define CONSOLE_RESET "\u001b[0;0H" << "\u001b[2J" << "\033[H\033[2J\033[3J"  // ANSI control character to reset cursor.

/**
 * @brief Constructor for when no matrix is provided.
 *
 * The constructor for abstract superclass `Renderer` is called with the provided parameters. There is no additional
 * implementation.
 * 
 * @param width the width of the matrix
 * @param height the height of the matrix
 */
ConsoleRenderer::ConsoleRenderer(int width, int height) : Renderer(width, height) {}

/**
 * @brief Constructor for when a pre-defined matrix is provided to display.
 * 
 * The constructor for abstract superclass `Renderer` is called with the provided parameters. There is no additional
 * implementation.
 *
 * @param matrix the 2D vector to be used to construct renderer (and to be displayed)
 */
ConsoleRenderer::ConsoleRenderer(const std::vector<std::vector<std::pair<std::string, Colour>>> &matrix) :
        Renderer(matrix) {}

/**
 * @brief Default destructor.
 * 
 * No memory is allocated.
 */
ConsoleRenderer::~ConsoleRenderer() = default;

/**
 * @brief Writes the textual representation of the provided matrix to the command line, given a 2D vector.
 * 
 * The string 2D vector is traversed and value within the array are printed. Pairs are used so that the colour of the
 * character on the board can be displayed. A border is drawn around the game matrix using Unicode box drawing
 * characters.
 *
 * @param matrix the matrix to be drawn
 */
void ConsoleRenderer::draw(const std::vector<std::vector<std::pair<std::string, Colour>>> &matrix) {
    std::cout << CONSOLE_RESET;
    drawHorizontal(true);
    for (int y = 0; y < height; y++) {
        std::cout << "│";
        for (int x = 0; x < width; x++) {
            printWithColour(matrix[y][x]);
        }
        std::cout << "│" << std::endl;
    }
    drawHorizontal(false);
    previousMatrix = matrix;
}

/**
 * @brief Updates the matrix displayed with the change provided at given coordinates.
 * 
 * Makes a change to the previously displayed matrix array and writes the textual representation of this new matrix to
 * the command line, given the position and new pair for the change to be made to the 2D vector.
 *
 * @param x the x-coordinate of the position in the matrix to be updated
 * @param y the y-coordinate of the position in the matrix to be updated
 * @param state the new pair of character and colour for the position to be updated
 * @throws runtime_error if there is no matrix to update (if the object is instantiated with no provided matrix)
 * @throws runtime_error if the provided index (x, y) is out of bounds
 */
void ConsoleRenderer::draw(int x, int y, std::pair<std::string, Colour> state) {
    if (previousMatrix.empty()) {
        throw std::runtime_error("no matrix exists to update");
    }
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::runtime_error("index out of bounds");
    }
    previousMatrix[y][x] = state;
    draw(previousMatrix);
}

/**
 * @brief Displays in-game menu.
 *
 * With a provided menu text string and a vector containing all of the menu options, the menu is written to the command
 * line. Input is not handled here.
 *
 * An empty option can be added to create a space between options (visually grouping them).
 *
 * @param menuText the text displayed at the top of the menu (e.g., the question)
 * @param options vector containing list of options the user may select
 */
void ConsoleRenderer::displayMenu(std::string menuText, std::vector<std::string> options) {
    std::cout << CONSOLE_RESET;
    std::cout << menuText << std::endl << std::endl;
    for (int i = 0; i < options.size(); i++) {
        if (!options[i].empty()) {
            std::cout << "  [" << i + 1 << "] " << options[i] << std::endl;
        } else {
            options.erase(options.begin() + i);
            i--;
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

/**
 * @brief Prints a message to the console.
 *
 * The console reset can be disabled to allow messages to be displayed one after the other where applicable.
 *
 * @param message the message to be reset
 * @param reset whether the console should be reset
 */
void ConsoleRenderer::displayMessage(std::string message, bool reset) {
    if (reset) {
        std::cout << CONSOLE_RESET;
    }
    std::cout << message << std::endl;
}

/**
 * @brief Writes top and bottom of box surrounding matrix.
 *
 * Unicode box drawing characters are used to create a border around the game matrix.
 *
 * @param top true if the top of the box is being written, false if the bottom of the box is being written
 */
void ConsoleRenderer::drawHorizontal(bool top) {
    std::cout << (top ? "┌" : "└");
    for (int i = 0; i < width; i++) {
        std::cout << "─";
    }
    std::cout << (top ? "┐" : "┘") << std::endl;
}

/**
 * @brief Prints the character of the provided pair to the terminal in the provided colour.
 *
 * The basic 8 ANSI terminal colours are supported here, with a default value of black if the colour is unsupported.
 *
 * @param pair the character `Colour` pair to be printed
 */
void ConsoleRenderer::printWithColour(const std::pair<std::string, Colour> &pair) {
    if (pair.second == Colour::TERMINAL_DEFAULT) {
        std::cout << pair.first;
    } else {
        std::cout << "\u001b[";
        switch (pair.second) {
            case Colour::BLACK:
                std::cout << 30;
                break;
            case Colour::RED:
                std::cout << 31;
                break;
            case Colour::GREEN:
                std::cout << 32;
                break;
            case Colour::YELLOW:
                std::cout << 33;
                break;
            case Colour::BLUE:
                std::cout << 34;
                break;
            case Colour::MAGENTA:
                std::cout << 35;
                break;
            case Colour::CYAN:
                std::cout << 36;
                break;
            case Colour::WHITE:
                std::cout << 37;
                break;
            default:
                std::cout << 30;
        }
        std::cout << "m" << pair.first << "\u001b[0m";
    }
}
