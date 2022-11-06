/**
 * File contains declaration for concrete `Pong` class.
 *
 * @file Pong.h
 * @co_author https://github.com/Jon-AL
 * @date 07/11/21
 */

#ifndef PONG_H
#define PONG_H

#include "../Game.h"

/**
 * @brief Declaration for concrete `Pong` class.
 *
 * Class provides an implementation of abstract superclass `Game` to be played. It provides appropriate constructor,
 * destructor and gameplay method implementations.
 */
class Pong : public Game {
private:
    using timer = std::chrono::steady_clock;
    int AICount;
    int difficulty[2];
    int scores[2];

    void tick() override;

    void displayGameTime();

    void updateBoard(std::vector<std::vector<std::pair<std::string, Colour>>> *gameBoard, Entity *entity, int width, int height, const std::pair<std::string, Colour> &newValue);

    void displayScore();

    void clearMessage(int length, int displacement = 0);

    void checkBallScored(Entity *ball);

    void score(int player);

public:
    explicit Pong(Renderer *renderer, int maxScore, int maxTime);

    ~Pong() override;

    void runGameLoop() override;
};

#endif
