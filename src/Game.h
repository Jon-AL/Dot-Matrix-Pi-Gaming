/**
 * File contains declaration of abstract `Game` class.
 *
 * @file Game.h
 * @co_author https://github.com/Jon-AL
 * @date 07/11/21
 */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <map>
#include "Entity.h"
#include "renderer/Renderer.h"
#include "ScoreRecorder.h"

/**
 * @brief Declaration for abstract `Game` class.
 *
 * Class provides declarations required for concrete subclass implementation. Definitions are provided for a base
 * constructor only.
 */
class Game {
protected:
    Renderer *renderer;
    ScoreRecorder *scoreRecorder;
    int maxScore;
    int maxTime;
    std::map<std::string, Entity *> entities;
    std::vector<std::vector<std::pair<std::string, Colour>>> gameBoard;
    bool gameFinished;
    bool gamePaused;
    int tickCount;

    virtual void tick() = 0;

public:
    explicit Game(Renderer *renderer, const std::string &filename, int maxScore, int maxTime);

    virtual ~Game() = 0;

    virtual void exitMenu();

    virtual void registerHighScore(int playerNo);

    virtual void displayMessage(const std::string &message, int displacement);

    virtual void runGameLoop() = 0;

};

#endif
