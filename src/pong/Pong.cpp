/**
 * File contains concrete definition of `Pong` subclass with appropriate static helper functions.
 *
 * @file Pong.cpp
 * @co_author https://github.com/Jon-AL
 * @date 07/11/21
 */

#include <iostream>
#include "../InputWatcher.h"
#include "Pong.h"
#include "Ball.h"
#include "Paddle.h"

#define SCORES_FILE "pong"

#define EMPTY_INDEX std::make_pair(" ", Colour::TERMINAL_DEFAULT)
#define BALL_INIT_X (renderer->getWidth() / 2)
#define BALL_INIT_Y (renderer->getHeight() / 2)
#define BALL_INIT_X_VEL 1
#define BALL_INIT_Y_VEL 1
#define BALL_INIT_WIDTH 1
#define BALL_INIT_HEIGHT 1
#define L_PADDLE_INIT_X 1
#define R_PADDLE_INIT_X (renderer->getWidth() - 2)
#define PADDLE_INIT_Y (renderer->getHeight() / 2)
#define PADDLE_INIT_VEL 0
#define PADDLE_INIT_WIDTH 1
#define PADDLE_INIT_HEIGHT 7  // should be odd.
#define TICK_LENGTH 50
#define PAUSE 27
#define P1_UP 'w'
#define P1_DOWN 's'
#define P2_UP 'u'
#define P2_DOWN 'j'

/**
 * @brief Executes a game tick.
 *
 * Each entity on the board is removed, updated and redrawn onto the board before the board is displayed to the user.
 */
void Pong::tick() {
    // Process user input.
    char input;
    while ((input = InputWatcher::getInstance().getKeyPress()) != '\0') {
        updateBoard(&gameBoard, entities["leftPaddle"], (int)entities["leftPaddle"]->getWidth(),
                    (int)entities["leftPaddle"]->getHeight(), EMPTY_INDEX);
        updateBoard(&gameBoard, entities["rightPaddle"], (int)entities["rightPaddle"]->getWidth(),
                    (int)entities["rightPaddle"]->getHeight(), EMPTY_INDEX);
        switch (input) {
            case PAUSE:
                gamePaused = true;
                break;
            case P1_UP:
                if(this->AICount <= 1){
                    if (entities["leftPaddle"]->getY() - 1 >= entities["leftPaddle"]->getHeight() / 2) {
                       entities["leftPaddle"]->setY(entities["leftPaddle"]->getY() - 1);
                    }
                }
                break;
            case P1_DOWN:
                if(this->AICount <= 1){
                    if (entities["leftPaddle"]->getY() + 1 <=
                        renderer->getHeight() - entities["leftPaddle"]->getHeight() / 2 - 1) {
                        entities["leftPaddle"]->setY(entities["leftPaddle"]->getY() + 1);
                    }
                }
                break;
            case P2_UP:
                if(this->AICount < 1){
                    if (entities["rightPaddle"]->getY() - 1 >= entities["rightPaddle"]->getHeight() / 2) {
                        entities["rightPaddle"]->setY(entities["rightPaddle"]->getY() - 1);
                    }
                }
                break;
            case P2_DOWN:
                if(this->AICount < 1){
                    if (entities["rightPaddle"]->getY() + 1 <=
                        renderer->getHeight() - entities["rightPaddle"]->getHeight() / 2 - 1) {
                        entities["rightPaddle"]->setY(entities["rightPaddle"]->getY() + 1);
                    }
                }
            default:
                break;
        }
        updateBoard(&gameBoard, entities["leftPaddle"], (int)entities["leftPaddle"]->getWidth(),
                    (int)entities["leftPaddle"]->getHeight(), entities["leftPaddle"]->getDisplayPair());
        updateBoard(&gameBoard, entities["rightPaddle"], (int)entities["rightPaddle"]->getWidth(),
                    (int)entities["rightPaddle"]->getHeight(), entities["rightPaddle"]->getDisplayPair());
    }
    // Updates all entities on the board.
    int count = -1;
    for (auto const &entity: entities) {
        int width = (int)entity.second->getWidth();
        int height = (int)entity.second->getHeight();
        updateBoard(&gameBoard, entity.second, width, height, EMPTY_INDEX);
        entity.second->update(entities, renderer->getWidth(), renderer->getHeight());
        if (entity.first == "ball") {
            checkBallScored(entity.second);
        }
        updateBoard(&gameBoard, entity.second, width, height, entity.second->getDisplayPair());
        count++;
    }
    displayGameTime();
    displayScore();
    renderer->draw(gameBoard);
}

/**
 * @brief Adds game time to game board.
 *
 * Uses the start time of the game compared to the current time to calculate the game time elapsed. This is added to the
 * middle of the board.
 */
void Pong::displayGameTime() {
    int elapsed = tickCount * TICK_LENGTH;
    long rawSeconds = elapsed / 1000;
    long minutes = rawSeconds / 60;
    long seconds = rawSeconds % 60;
    std::string minutesStr = std::to_string(minutes);
    if (minutesStr.length() < 2) {
        minutesStr = "0" + minutesStr;
    }
    std::string secondsStr = std::to_string(seconds);
    if (secondsStr.length() < 2) {
        secondsStr = "0" + secondsStr;
    }
    std::string gameTime = minutesStr + ":" + secondsStr;
    if (maxTime != 0 && minutes == maxTime) {
        if (scores[0] == scores[1]) {
            displayMessage("The game was a tie!", -2);
        } else {
            displayMessage("Congratulations player " + std::to_string(scores[0] > scores[1] ? 1 : 2) + ", you win!",
                           -2);
        }
        displayMessage("Press any key to return to the main menu", 0);
        renderer->draw(gameBoard);
        while (InputWatcher::getInstance().getKeyPress() == '\0');
        gameFinished = true;
    }
    int middle = gameBoard[0].size() / 2;
    for (int i = 0; i < gameTime.length(); i++) {
        gameBoard[1][middle + i - 2] = std::make_pair(gameTime[i], Colour::TERMINAL_DEFAULT);
    }
}

/**
 * @brief Static helper function updates the game board for entities.
 *
 * With the provided game board, entity, width, height and pair of character and `Colour`, the game board is updated to
 * either add or remove the entity, by setting the values at its position to true or false respectively.
 *
 * @param gameBoard pointer to the game board
 * @param entity the entity to be added/removed
 * @param width the width of the entity (passed to prevent repeated calls to getter in calling method)
 * @param height the height of the entity (passed to prevent repeated calls to getter in calling method)
 * @param newValue the value that the entities positions should be set to
 */
void Pong::updateBoard(std::vector<std::vector<std::pair<std::string, Colour>>> *gameBoard, Entity *entity, int width,
                 int height, const std::pair<std::string, Colour> &newValue) {
    for (int x = (int)entity->getX() - ((width - 1) / 2); x <= (int)entity->getX() + (width - 1) / 2; x++) {
        for (int y = (int)entity->getY() - ((height - 1) / 2); y <= (int)entity->getY() + (height - 1) / 2; y++) {
            if(x >= renderer->getWidth() || y >= renderer->getHeight()) continue;
            gameBoard->at(y).at(x) = newValue;
        }
    }
}

/**
 * @brief Static helper function gets the game type from the user.
 *
 * The user will be displayed a menu which will persist until the input a valid option. They may select a human versus
 * human, human versus AI or AI versus AI game.
 *
 * @param renderer the game renderer
 * @return the integer representation of the game time (the number of AI players)
 */
int getAICountFromUser(Renderer *renderer) {
    renderer->displayMenu("Please select a game type:", {"You versus Human Opponent", "You versus AI", "AI versus AI"});
    char input;
    while (true) {
        if ((input = InputWatcher::getInstance().getKeyPress()) != '\0') {
            switch (input) {
                case '1':
                case '2':
                case '3':
                    return input - '0' - 1;
                default:
                    continue;
            }
        }
    }
}

/**
 * @brief Static helper function gets the AI difficulty level from the user.
 *
 * The user will be displayed a menu which will persist until they choose a valid option. They may choose from four
 * difficulties. This method can be called for as many AI players exist in the game.
 *
 * @param renderer the game renderer
 * @param playerNo the player number (to be displayed to the user)
 * @return the difficulty level of the AI
 */
int getAIDifficultyFromUser(Renderer *renderer, int playerNo) {
    renderer->displayMenu("Please select a difficulty level for player " + std::to_string(playerNo) + ":",
                          {"Easy", "Moderate", "Hard", "Extreme"});
    char input;
    while (true) {
        if ((input = InputWatcher::getInstance().getKeyPress()) != '\0') {
            switch (input) {
                case '1':
                case '2':
                case '3':
                case '4':
                    return input - '0' - 1;
                default:
                    continue;
            }
        }
    }
}

/**
 * @brief Constructor for new game instance using provided renderer .
 *
 * The constructor for abstract superclass `Game` is called with the provided parameters. In addition, a game board is
 * initialised as a 2D vector of size provided by the renderer, with default values set to empty, and a vector of
 * required entities is also initialised.
 *
 * @param renderer the provided instance of `Renderer` to be used to display the game
 * @param maxScore the maximum score of the game
 * @param maxTime the maximum time of the game
 */
Pong::Pong(Renderer *renderer, int maxScore, int maxTime) : Game(renderer, SCORES_FILE, maxScore, maxTime) {
    for (int y = 0; y < renderer->getHeight(); y++) {
        std::vector<std::pair<std::string, Colour>> row;
        for (int x = 0; x < renderer->getWidth(); x++) {
            row.emplace_back(EMPTY_INDEX);
        }
        this->gameBoard.push_back(row);
    }

    this->AICount = getAICountFromUser(renderer);
    this->difficulty[0] = this->AICount > 1 ? getAIDifficultyFromUser(renderer, 1) : -1;
    this->difficulty[1] = this->AICount > 0 ? getAIDifficultyFromUser(renderer, 2) : -1;

    this->entities["ball"] = new Ball(BALL_INIT_X, BALL_INIT_Y, BALL_INIT_X_VEL, BALL_INIT_Y_VEL, BALL_INIT_WIDTH,
                                      BALL_INIT_HEIGHT, Colour::TERMINAL_DEFAULT);
    this->entities["leftPaddle"] = new Paddle(L_PADDLE_INIT_X, PADDLE_INIT_Y, PADDLE_INIT_VEL, PADDLE_INIT_VEL,
                                              PADDLE_INIT_WIDTH, PADDLE_INIT_HEIGHT, Colour::RED, AICount>=2, this->difficulty[0]);
    this->entities["rightPaddle"] = new Paddle(R_PADDLE_INIT_X, PADDLE_INIT_Y, PADDLE_INIT_VEL, PADDLE_INIT_VEL,
                                               PADDLE_INIT_WIDTH, PADDLE_INIT_HEIGHT, Colour::BLUE, AICount>=1, this->difficulty[1]);

    this->scores[0] = 0;
    this->scores[1] = 0;

    // Display "press any key" screen
    std::string instructionMessage = "score a point by bypassing your opponent's paddle!";
    std::string player1Message = "Player 1: use keys W and S to move your paddle up and down respectively";
    std::string player2Message = "Player 2: use keys U and J to move your paddle up and down respectively";
    std::string pauseMessage = "Pause the game at any time using the escape key";
    std::string beginMessage = "Press any key to begin";
    displayMessage(instructionMessage, -6);
    if (AICount < 2) {
        displayMessage(player1Message, -4);
    }
    if (AICount == 0) {
        displayMessage(player2Message, -3);
    }
    displayMessage(pauseMessage, -2);
    displayMessage(beginMessage, 0);
    renderer->draw(gameBoard);
    while (InputWatcher::getInstance().getKeyPress() == '\0');
    clearMessage(instructionMessage.length(), -6);
    clearMessage(player1Message.length(), -4);  // Extra, unnecessary clears are OK.
    clearMessage(player2Message.length(), -3);
    clearMessage(pauseMessage.length(), -2);
    clearMessage(beginMessage.length());
}

/**
 * @brief Adds the score to the board.
 *
 * The score is displayed in front of each players paddle.
 */
void Pong::displayScore() {
    std::string score1 = std::to_string(scores[0]);
    std::string score2 = std::to_string(scores[1]);
    int middle = gameBoard.size() / 2;
    for (int i = 0; i < score1.length(); i++) {
        gameBoard[middle][L_PADDLE_INIT_X + 2 + i] = std::make_pair(score1[i], Colour::TERMINAL_DEFAULT);
    }
    for (int i = 0; i < score2.length(); i++) {
        gameBoard[middle][R_PADDLE_INIT_X - 2 - i] = std::make_pair(score2[i], Colour::TERMINAL_DEFAULT);
    }
}

/**
 * @brief Clears the board with a message.
 */
void Pong::clearMessage(int length, int displacement /* = 0 */) {
    displayMessage(std::string(length, ' '), displacement);
}


/**
 * @brief Function to determine whether or not a ball has scored AFTER it updates it's position. Resets the ball
 * accordingly.
 *
 * Given that the ball entity has updated it's position, we can determine whether or not
 * a score must be given to a player.
 *
 * @param ball pointer to a ball on the board
 */
void Pong::checkBallScored(Entity *ball) {
    if (ball->getX() <= 0) {
        score(1);
        ball->setX(BALL_INIT_X);
        ball->setY(BALL_INIT_Y);
    } else if (ball->getX() >= renderer->getWidth()) {
        score(0);
        ball->setX(BALL_INIT_X);
        ball->setY(BALL_INIT_Y);
    }
}

/**
 * @brief Destructs instance of `Pong`.
 *
 * Deletes all instances of `Entity` created for this game.
 */
Pong::~Pong() {
    for (auto &entity: entities) {
        delete entity.second;
    }
}

/**
 * @brief Runs game loop which operates game.
 *
 * Calls method `tick` to update the game. This method is called every 100 milliseconds. This happens by comparing the
 * current system time to the time `tick` was last called, calling it again after 100 milliseconds have elapsed.
 */
void Pong::runGameLoop() {
    auto lastTickTime = timer::now();  // gets the current game start time in milliseconds.

    // While the game loop is active...
    while (!gameFinished) {
        if (gamePaused) {
            exitMenu();
        } else {
            auto currentTime = timer::now();  // gets the current time in nanoseconds.
            if ((currentTime - lastTickTime) > std::literals::chrono_literals::operator ""ms(TICK_LENGTH)) {
                lastTickTime = timer::now();
                tick();  // runs a tick.
                tickCount++;
            }
        }
    }
}

/**
 * @brief Function to increase a player's score.
 *
 * When a player scores by having their opponent miss a ball, increase their score.
 *
 * @param player which player scored
 */
void Pong::score(int player) {
    scores[player]++;
    if (maxScore != 0 && scores[player] == maxScore) {
        registerHighScore(player + 1);
        displayMessage("Press any key to return to the main menu", 0);
        renderer->draw(gameBoard);
        while (InputWatcher::getInstance().getKeyPress() == '\0');
        gameFinished = true;
    }
}

