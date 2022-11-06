/**
 * File contains declaration for `ScoreRecorder` class.
 * @file ScoreRecorder.h
 * @co_authors https://github.com/Jon-AL
 * @date 26/11/21
 */

#ifndef SCORE_RECORDER_H
#define SCORE_RECORDER_H

#include <string>
#include <vector>
#include <fstream>

/**
 * @brief Declaration for `ScoreRecorder` class.
 *
 * Class provides a means to read and write to a high scores file, which will allow high scores to be stored at the end
 * of a game and to be displayed in a menu.
 *
 * Scores are written to file in format "<score> - <player_name>".
 */
class ScoreRecorder {
private:
    std::fstream file;

public:
    ScoreRecorder(const std::string &filename);

    ~ScoreRecorder();

    bool writeScore(const std::string &playerName, int score);

    std::vector<std::string> getHighScores(int noOfScores);
};

#endif
