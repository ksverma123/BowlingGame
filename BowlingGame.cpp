/*
Bowling Game calculator 
Author: Kshitiz Verma
email: kshitiz.rcet@gmail.com
contact: +917587430737
*/

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
using namespace std;

class Frame {
public:
    int score = 0;
    int rollIndex = 0;
    Frame(int index) { rollIndex = index; }
};

class BowlingGame {
    vector<int> rolls;

    int charToScore(char c, int prev = 0) {
        if (c == 'X' || c == 'x') return 10;
        if (c == '/') return 10 - prev;
        if (c >= '0' && c <= '9') return c - '0';
        throw invalid_argument(string("Invalid character in input: ") + c);
    }

    void parseInput(const string& input) {
        rolls.clear();
        int prev = 0;
        for (size_t i = 0; i < input.length(); ++i) {
            char c = input[i];
            int score = charToScore(c, prev);
            rolls.push_back(score);
            prev = (c == '/') ? 0 : score;
        }
    }

public:
    void scoreGame() {
        rolls.clear();
        string input;
        int frameNum = 0;

        cout << "Enter bowling scores (X for strike, / for spare):\n";
        while (frameNum < 10) {
            cout << "Enter " << frameNum + 1 << " Roll: ";
            cin >> input;

            if (input.empty()) {
                cout << "Invalid input. Try again.\n";
                continue;
            }

            try {
                if (frameNum < 9) {
                    if (input == "X" || input == "x") {
                        rolls.push_back(10);
                    } else if (input.length() == 2) {
                        int first = charToScore(input[0], 0);
                        int second = charToScore(input[1], first);
                        if (first + second > 10) {
                            cout << "Invalid frame. Total pins > 10.\n";
                            continue;
                        }
                        rolls.push_back(first);
                        rolls.push_back(second);
                    } else {
                        cout << "Invalid input. Try again.\n";
                        continue;
                    }
                } else {
                    // 10th frame logic
                    if (input.length() < 2 || input.length() > 3) {
                        cout << "Invalid input. Try again.\n";
                        continue;
                    }

                    int first = charToScore(input[0], 0);
                    int second = charToScore(input[1], first);

                    if ((first + second < 10) && input.length() == 3) {
                        cout << "Invalid input. No bonus allowed for open frame.\n";
                        continue;
                    }
                    if ((first + second >= 10) && input.length() != 3) {
                        cout << "Invalid input. Bonus roll required.\n";
                        continue;
                    }

                    rolls.push_back(first);
                    rolls.push_back(second);

                    if (input.length() == 3) {
                        int third = charToScore(input[2], second);
                        rolls.push_back(third);
                    }
                }

                frameNum++;
            } catch (...) {
                cout << "Invalid input. Try again.\n";
                continue;
            }
        }

        printScores();
    }

    int computeScoreFromString(const string& input) {
        parseInput(input);

        int score = 0;
        int rollIndex = 0;

        for (int frame = 0; frame < 10; ++frame) {
            if (rolls[rollIndex] == 10) { // Strike
                score += 10 + rolls[rollIndex + 1] + rolls[rollIndex + 2];
                rollIndex += 1;
            } else if (rolls[rollIndex] + rolls[rollIndex + 1] == 10) { // Spare
                score += 10 + rolls[rollIndex + 2];
                rollIndex += 2;
            } else { // Open
                score += rolls[rollIndex] + rolls[rollIndex + 1];
                rollIndex += 2;
            }
        }

        return score;
    }

    void printScores() {
        int score = 0;
        int rollIndex = 0;

        for (int frame = 0; frame < 10; ++frame) {
            if (rolls[rollIndex] == 10) {
                score += 10 + rolls[rollIndex + 1] + rolls[rollIndex + 2];
                rollIndex += 1;
            } else if (rolls[rollIndex] + rolls[rollIndex + 1] == 10) {
                score += 10 + rolls[rollIndex + 2];
                rollIndex += 2;
            } else {
                score += rolls[rollIndex] + rolls[rollIndex + 1];
                rollIndex += 2;
            }
            cout << "Frame " << frame + 1 << " Score: " << score << endl;
        }

        cout << "Total Score: " << score << endl;
    }
};

void runTests() {
    BowlingGame game;
    assert(game.computeScoreFromString("XXXXXXXXXXXX") == 300);  // Perfect game
    assert(game.computeScoreFromString("5/5/5/5/5/5/5/5/5/5/5") == 150); // All spares
    assert(game.computeScoreFromString("12345123451234512345") == 60); // Open frames
    assert(game.computeScoreFromString("X7/90X088/06XXX81") == 167); // Mixed
    assert(game.computeScoreFromString("90909090909090909090") == 90); // All 9 and miss
    assert(game.computeScoreFromString("1/1/1/1/1/1/1/1/1/1/1") == 110); // All 1/ + 1

    cout << "All tests passed!\n";
}

int main() {
    BowlingGame game;
    int selection;
    char ch = 'Y';

    while (ch == 'Y' || ch == 'y') {
        cout << "Enter number for Manual inputs or run Default unit tests?\n[1]. Manual input  \n[2]. Unit tests\n";
        cin >> selection;

        if (selection == 1) {
            try {
                game.scoreGame();
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << "\n";
            }
        } else {
            runTests();
        }

        cout << "Play Again??? (y/n)\n";
        cin >> ch;
    }

    return 0;
}
