/**
 * File contains declaration for concrete `DotMatrixRenderer` class.
 *
 * @file DotMatrixRenderer.h
 * @co_author https://github.com/Jon-AL
 * @date 05/11/21
 */

#ifndef DOT_MATRIX_RENDERER_H
#define DOT_MATRIX_RENDERER_H

#include "Renderer.h"

/**
 * @brief Declaration for concrete `DotMatrixRenderer` class.
 * 
 * Class provides an implementation of abstract superclass `Renderer` to be used to output to the command line. It 
 * provides appropriate constructor, destructor and draw method implementations.
 */
class DotMatrixRenderer : public Renderer {

public:
    DotMatrixRenderer(int width, int height);

    explicit DotMatrixRenderer(const std::vector<std::vector<std::pair<std::string, Colour>>> &matrix);

    ~DotMatrixRenderer() override;

    void draw(const std::vector<std::vector<std::pair<std::string, Colour>>> &matrix) override;

    void draw(int x, int y, std::pair<std::string, Colour> state) override;

    void displayMenu(std::string menuText, std::vector<std::string> options) override;

    void displayMessage(std::string message, bool reset) override;
};

#endif
