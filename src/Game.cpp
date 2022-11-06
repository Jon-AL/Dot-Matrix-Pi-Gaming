/**
 * File contains definition of abstract `Game` class.
 *
 * @file Game.cpp
 * @co_author https://github.com/Jon-AL
 * @date 07/11/21
 */

#include "Game.h"
#include "InputWatcher.h"
#include <iostream>

/**
 * @brief Basic base constructor
 *
 * Constructs new instance with the provided renderer, defaulting the active game status to true.
 *
 * @param renderer the instance of `Renderer` to be used to display the game
 * @param filename the file name of the game's high scores file
 * @param maxScore the maximum score of the game
 * @param maxTime the maximum time of the game
 */
Game::Game(Renderer *renderer, const std::string &filename, int maxScore, int maxTime) {
    this->renderer = renderer;
    this->scoreRecorder = new ScoreRecorder(filename);
    this->maxScore = maxScore;
    this->maxTime = maxTime;
    gameFinished = false;
    gamePaused = false;
    tickCount = 0;
}

/**
 * @brief Default destructor.
 *
 * Destroys the score recorder.
 */
Game::~Game() {
    delete scoreRecorder;
}

/**
 * @brief General exit menu.
 *
 * Constructs an exit menu that can be called with the push of the key p.
 */
void Game::exitMenu() {
    renderer->displayMenu("Game paused, do you wish to continue?",
                          {"Yes, resume!", "No, exit - all of your progress will be lost"});
    char input;
    while (true) {
        if ((input = InputWatcher::getInstance().getKeyPress()) != '\0') {
            switch (input) {
                case '1':
                    gamePaused = false;
                    break;
                case '2':
                    gameFinished = true;
                    break;
                default:
                    continue;
            }
        }
        if (input == '1' || input == '2') {
            break;
        }
    }
}


void Game::registerHighScore(int playerNo) {
    displayMessage("Congratulations player " + std::to_string(playerNo) + ", you win!", -6);
    displayMessage("Enter a 3 letter name to register your score:", -4);
    renderer->draw(gameBoard);
    std::string result;
    char input;
    while (true) {
        if ((input = InputWatcher::getInstance().getKeyPress()) != '\0') {
            if (input >= 'a' && input <= 'z') {
                input -= 32;
                result.append(std::string{input});
                displayMessage(result, -3);
                renderer->draw(gameBoard);
                if (result.length() == 3) {
                    break;
                }
            }
        }
    }
    if (scoreRecorder->writeScore(result, maxScore)) {
        displayMessage("Your score has been registered, " + result + "!", -2);
    } else {
        displayMessage("Your score was unable to be recorded due to an unforeseen error", -2);
    }
}

void Game::displayMessage(const std::string &message, int displacement) {
    int midX = gameBoard[0].size() / 2;
    int midY = gameBoard.size() / 2;
    int strMid = message.length() / 2;
    for (int i = 0; i < message.length(); i++) {
        gameBoard[midY + displacement][midX - strMid + i] = std::make_pair(message[i], Colour::TERMINAL_DEFAULT);
    }
}
