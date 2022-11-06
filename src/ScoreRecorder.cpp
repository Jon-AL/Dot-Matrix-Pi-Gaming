/**
 * File contains definition of `ScoreRecorder` class.
 *
 * @file ScoreRecorder.cpp
 * @co_author https://github.com/Jon-AL
 * @date 26/11/21
 */

#include <fstream>
#include <filesystem>
#include <algorithm>
#include "ScoreRecorder.h"

#define PATH "scores/"  // relative path to directory containing stored files.
#define EXT ".high"  // stored file extension.

/**
 * @brief Basic constructor to initialise new instance of `ScoreRecorder`.
 *
 * A new file stream is opened using the provided extension along with the defined path and file extension. A new file
 * will be created if the file does not exist.
 *
 * @param filename the name of the high score file for a particular game
 */
ScoreRecorder::ScoreRecorder(const std::string &filename) {
    file.open(PATH + filename + EXT, std::ios::in | std::ios::out | std::ios::app);
}

/**
 * @brief Basic destructor to destroy `ScoreRenderer` instance.
 *
 * Closes the opened file.
 */
ScoreRecorder::~ScoreRecorder() {
    file.close();
}

/**
 * @brief Allows strings to be written to the open file.
 *
 * Checks to ensure the file is open as expected, and that the write operation is successful.
 *
 * @param playerName the name of the user, input when prompted
 * @param score the player's score
 * @return true if the write operation was successful, false if an error occurred
 */
bool ScoreRecorder::writeScore(const std::string &playerName, int score) {
    if (file.is_open()) {
        file << score << " - " << playerName << std::endl;
    } else {
        return false;
    }
    return file.good();
}

/**
 * @brief Reads lines from the high score file.
 *
 * Only the number of specified files will be read. The scores are sorted into descending order before being returned.
 *
 * @param noOfScores the number of lines to be read
 * @return the vector of lines read
 */
std::vector<std::string> ScoreRecorder::getHighScores(int noOfScores) {
    std::vector<std::string> lines;
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
    }
    std::sort(lines.begin(), lines.end(), std::greater<>());
    lines.resize(noOfScores);
    return lines;
}

