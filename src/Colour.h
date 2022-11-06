/**
 * File contains declaration for `Colour` enumeration class.
 *
 * @file Colour.h
 * @co_author https://github.com/Jon-AL
 * @date 24/11/21
 */

#ifndef COLOUR_H
#define COLOUR_H

/**
 * @brief Declaration of `Colour` enumeration.
 *
 * Currently supports the 8 standard ANSI terminal colours.
 */
enum class Colour {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    TERMINAL_DEFAULT
};

#endif
