/**
 * File contains definition of `GameInstance` class which runs the program.
 *
 * @file GameInstance.cpp
 * @co_author https://github.com/Jon-AL
 * @date 05/11/21
 */

#include <iostream>
#include <string>
#include <vector>
#include "InputWatcher.h"
#include "renderer/ConsoleRenderer.h"
#include "renderer/DotMatrixRenderer.h"
#include "pong/Pong.h"

#define BOARD_WIDTH 101
#define BOARD_HEIGHT 31

int pongMaxScore = 5;
int pongMaxTime = 2;  // minutes.

/**
 * @brief Static helper function gets new settings numerical value.
 *
 * The numerical inputs of the user are appended to a string until the user enters an alphabetical character, at which
 * point it is returned as an integer.
 *
 * @param renderer the renderer to display the menu
 * @return the new value input by the user
 */
int getNewValue(Renderer *renderer) {
    renderer->displayMessage("Please enter the new numerical value:", true);
    std::string result = "0";
    char input;
    while (true) {
        if ((input = InputWatcher::getInstance().getKeyPress()) != '\0') {
            if (input >= '0' && input <= '9') {
                std::cout << input << std::flush;
                result.append(std::string{input});
            } else if (input == '\n') {
                return std::stoi(result);
            }
        }
    }
}

/**
 * @brief Static helper function displays the settings menu.
 *
 * Allows the user to set the maximum score and time for each game.
 *
 * @param renderer the renderer to display the menu
 */
void displaySettings(Renderer *renderer) {
    std::string message = "Select a value to change, or return to the main menu:\n"
                          "Note: limits can be removed by setting the limit value to zero, but you won't be able to "
                          "record your high score!";
    std::vector<std::string> options = {"Pong Maximum Game Score = " + std::to_string(pongMaxScore),
                                        "Pong Maximum Game Duration = " + std::to_string(pongMaxTime),
                                        "",
                                        "Return to Main Menu"};
    renderer->displayMenu(message, options);
    char input;
    while (true) {
        if ((input = InputWatcher::getInstance().getKeyPress()) != '\0') {
            switch (input) {
                case '1':
                    pongMaxScore = getNewValue(renderer);
                    options[0] = "Pong Maximum Game Score = " + std::to_string(pongMaxScore);
                    renderer->displayMenu(message, options);
                    break;
                case '2':
                    pongMaxTime = getNewValue(renderer);
                    options[1] = "Pong Maximum Game Duration = " + std::to_string(pongMaxTime);
                    renderer->displayMenu(message, options);
                    break;
                case '3':
                    return;
                default:
                    continue;
            }
        }
    }
}

/**
 * @brief Static helper function prompts the user to select a game from which to see high scores.
 *
 * The name of the game (all lowercase) is returned with the expectation that this is the filename.
 *
 * @param renderer the renderer to display the menu
 * @return the name of the game
 */
std::string selectHighScoresGame(Renderer *renderer) {
    std::string message = "Select a game to view its high scores:";
    std::vector<std::string> options = {"Pong"};
    renderer->displayMenu(message, options);
    char input;
    while (true) {
        if ((input = InputWatcher::getInstance().getKeyPress()) != '\0') {
            switch (input) {
                case '1':
                    return "pong";
                default:
                    continue;
            }
        }
    }
}

/**
 * @brief Static helper function displays the high scores.
 *
 * The user is prompted to select a game and then the high scores are displayed.
 *
 * @param renderer the renderer to display the menu
 */
void displayHighScores(Renderer *renderer) {
    std::string filename = selectHighScoresGame(renderer);
    ScoreRecorder *scoreRecorder = new ScoreRecorder("pong");
    filename[0] = toupper(filename[0]);
    renderer->displayMessage(filename + " high scores:\n", true);
    std::vector<std::string> lines = scoreRecorder->getHighScores(5);
    int lineCount = 0;
    for (std::string line: lines) {
        if (line.length() > 0) {
            renderer->displayMessage(line, false);
            lineCount++;
        }
    }
    if (lineCount == 0) {
        renderer->displayMessage("No scores to display", false);
    }
    renderer->displayMessage("\nPress any key to return to the main menu", false);
    while (InputWatcher::getInstance().getKeyPress() == '\0');
    delete scoreRecorder;
}

/**
 * @brief Gets desired output method for user.
 *
 * Prompts user to select output method and returns appropriate instance of abstract superclass `Renderer`.
 *
 * @param width the width of the display
 * @param height the height of the display
 * @return pointer to the instance of abstract `Renderer` instantiated
 */
Renderer *selectOutput(int width, int height) {
    std::cout << "\033[H\033[2J\033[3J"; // linux specific 'clear' sequence to clear the terminal.
    std::cout << "Confirm an output method and press enter to continue:" << std::endl;
    std::cout << "Note: this cannot be changed later." << std::endl << std::endl;
    std::cout << "  [1] Command Line" << std::endl;
    std::cout << "  [2] Dot Matrix" << std::endl;
    std::cout << std::endl;
    std::string user_selection;
    std::cin >> user_selection;
    while (user_selection != "1" && user_selection != "2") {
        std::cout << std::endl << "Please enter a valid option:" << std::endl;
        std::cin >> user_selection;
    }
    if (user_selection == "1") {
        return new ConsoleRenderer(width, height);
    }
    return new DotMatrixRenderer(width, height);
}

/**
 * @brief Gets desired game to be played from the user.
 *
 * Prompts user to select game and returns appropriate instance of abstract superclass `Game`.
 *
 * @param renderer the instance of abstract superclass `Renderer` to be used to display the game selected
 * @return pointer to the instance of abstract `Game` instantiated
 */
Game *selectGame(Renderer *renderer) {
    std::string message = "Welcome! The game will now detect your keystrokes; there's no need to press enter!\n\n"
                          "Select a game to play or an option from below:";
    std::vector<std::string> options = {"Pong", "", "View High Scores", "Settings", "Exit"};
    renderer->displayMenu(message, options);
    char input;
    while (true) {
        if ((input = InputWatcher::getInstance().getKeyPress()) != '\0') {
            switch (input) {
                case '1':
                    return new Pong(renderer, pongMaxScore, pongMaxTime);
                case '2':
                    displayHighScores(renderer);
                    renderer->displayMenu(message, options);
                    continue;
                case '3':
                    displaySettings(renderer);
                    renderer->displayMenu(message, options);
                    continue;
                case '4':
                    return nullptr;
                default:
                    continue;
            }
        }
    }
}

/**
 * @brief Main function executes program.
 *
 * Initialises a new instance of `Renderer` and `Game` based on the user's selections and runs the game loop of the game
 * selected.
 *
 * @return 0 on successful execution
 */
int main() {
    Renderer *renderer = selectOutput(BOARD_WIDTH, BOARD_HEIGHT);
    InputWatcher::getInstance();  // ensure InputWatcher singleton is initialised.
    while (true) {
        Game *game = selectGame(renderer);
        if (game == nullptr) {
            break;
        }
        game->runGameLoop();
        delete game;
    }
    delete renderer;
    return 0;
}
