/**
 * File contains declaration for singleton `InputWatcher` class.
 *
 * @file InputWatcher.h
 * @co_author https://github.com/Jon-AL
 * @date 23/11/21
 */

#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <vector>
#include <queue>
#include <thread>

/**
 * @brief Declaration for singleton `InputWatcher` class.
 *
 * Class provides an implementation of singleton class `InputWatcher` which will record user keystrokes to be used as
 * game input. This class shall use the singleton design pattern as it makes changes to the user's terminal, and it must
 * be ensured that these changes are reverted upon program termination.
 */
class InputWatcher {
private:
    static InputWatcher *instance;
    std::queue<char> keyPresses;
    std::vector<std::thread> ioThread;

    InputWatcher();

    static void setTerminalModeRaw();

    static void resetTerminalMode();

public:
    static InputWatcher &getInstance();

    char getKeyPress();
};

#endif
