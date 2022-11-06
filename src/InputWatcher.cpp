/**
 * File contains definition of `InputWatcher` class with appropriate static helper functions.
 *
 * @file InputWatcher.cpp
 * @co_author https://github.com/Jon-AL
 * @date 23/11/21
 */

#include <cstdlib>
#include <unistd.h>
#include <termios.h>
#include "InputWatcher.h"

InputWatcher *InputWatcher::instance = nullptr;  // initialises instance variable to null.

/**
 * @brief Constructor initialises new instance of `InputWriter`.
 *
 * This constructor is private due to the singleton nature of the class. The terminal mode is first set to "raw". A
 * detached background thread is then initialised which reads characters from standard input and queues them.
 */
InputWatcher::InputWatcher() {
    setTerminalModeRaw();
    ioThread.emplace_back([this] {
        char c;
        while (read(STDIN_FILENO, &c, 1) == 1) {
            this->keyPresses.push(c);
        }
    });
    ioThread[0].detach();
}

struct termios origTermios;  // struct to store original settings of user terminal.

/**
 * @brief Helper function sets the user's terminal to "raw" mode.
 *
 * The user's terminal is set to return single characters to standard input, as opposed to "cooked" full lines. In
 * addition, character echoing is disabled, to prevent the game board becoming malformed.
 *
 * This function was written following an online tutorial which can be found at:
 * https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
 */
void InputWatcher::setTerminalModeRaw() {
    tcgetattr(STDIN_FILENO, &origTermios);
    atexit(resetTerminalMode);

    struct termios raw = origTermios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

/**
 * @brief Helper function resets user's terminal to its settings before a game was launched.
 *
 * This function justifies the use of singleton design pattern: if a second instance of `InputWatcher` was declared, the
 * "original settings" stored would be the altered settings set by the first instance, potentially resulting in the
 * original settings becoming lost, depending on the order of termination.
 *
 * This function was written following an online tutorial which can be found at:
 * https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
 */
void InputWatcher::resetTerminalMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &origTermios);
}

/**
 * @brief Returns current instance of singleton `InputWriter`.
 *
 * If an instance does not exist, it is first initialised, before the current instance is returned.
 *
 * @return the current (and only) instance of `InputWriter`
 */
InputWatcher &InputWatcher::getInstance() {
    if (instance == nullptr) {
        instance = new InputWatcher();
    }
    return *instance;
}

/**
 * @brief Gets the character at the front of the queue.
 *
 * Characters read from standard input are queued, with the front of the queue being read and popped here. If the queue
 * is empty, the null character ('\0') is returned.
 *
 * @return the character at the front of the queue, '\0' if the queue is empty
 */
char InputWatcher::getKeyPress() {
    if (keyPresses.empty()) {
        return '\0';
    }
    char front = keyPresses.front();
    keyPresses.pop();
    return front;
}
