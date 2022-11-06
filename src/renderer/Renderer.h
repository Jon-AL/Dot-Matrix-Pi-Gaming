/**
 * File contains declaration of abstract `Renderer` class.
 *
 * @file Renderer.h
 * @co_author https://github.com/Jon-AL
 * @date 28/10/21
 */

#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <vector>
#include "../Colour.h"

/**
 * @brief Declaration for abstract `Renderer` class.
 *
 * Class provides declarations required for concrete subclass implementation. Definitions are provided for constructors,
 * a destructor and basic getter/setter methods.
 */
class Renderer {

protected:
    int width;
    int height;
    std::vector<std::vector<std::pair<std::string, Colour>>> previousMatrix;

public:
    Renderer(int width, int height);

    explicit Renderer(const std::vector<std::vector<std::pair<std::string, Colour>>> &matrix);

    virtual ~Renderer() = 0;

    int getWidth() const;

    int getHeight() const;

    virtual void draw(const std::vector<std::vector<std::pair<std::string, Colour>>> &matrix) = 0;

    virtual void draw(int x, int y, std::pair<std::string, Colour> state) = 0;

    virtual void displayMenu(std::string menuText, std::vector<std::string> options) = 0;

    virtual void displayMessage(std::string message, bool reset) = 0;
};

#endif
