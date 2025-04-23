#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <fstream>
#include <string>

using namespace std;

int loadHighScore(const string& filename) {
    ifstream file(filename);
    int score = 0;
    if (file >> score) return score;
    return 0;
}

void saveHighScore(const string& filename, int score) {
    ofstream file(filename);
    if (file.is_open()) {
        file << score;
    }
}

#endif // SCORE_H_INCLUDED
