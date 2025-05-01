/*
Bowling Game calculator 
Author: Kshitiz Verma
email: kshitiz.rcet@gmail.com
contact: +917587430737
*/

#include<iostream>
#include <vector>
#include <string>
#include<cassert>
using namespace std;
void runTests();
/*

Class frame takes care of tracking score per frame and starting index of roll

*/
class Frame {
public:
    int score = 0;
    int rollIndex = 0;  // Index of the first roll of this frame in the roll list
    Frame(int index) { rollIndex=index;}
};

class BowlingGame {
    vector<int> rolls;  //to store int vales scored each roll
    vector<Frame> frames; // to store all instances of frame class

    int charToScore(char c, int prev = 0) {
        if (c == 'X' || c == 'x') return 10;  // Strike
        if (c == '/') return 10 - prev;  // Spare
        if (c >= '0' && c <= '9') return c - '0';  // Valid digit
        throw invalid_argument(string("Invalid character in input: ") + c);  // Handle invalid chars
    }
     

    void parseInput(const string& input) {
        rolls.clear();
        int prev = 0;
        for (char c : input) {
            int pins = charToScore(c, prev);
            rolls.push_back(pins);
            prev = (c == '/') ? 0 : pins;
        }
    }

public:
    int scoreGame(const string& input) {
        parseInput(input);
        frames.clear();
        int i = 0;
        int f;
        for ( f = 0; f < 10 && i< rolls.size(); f++) {
            Frame frame(i);
            if (rolls[i] == 10) {  // Strike
                frame.score = 10 + rolls[i+1] + rolls[i+2]; //Bonus is next two frames
                i += 1;
            } else if (rolls[i] + rolls[i+1] == 10) {  // Spare
                frame.score = 10 + rolls[i+2]; //Bonus is next frame
                i += 2;
            } else {  // Open frame
                frame.score = rolls[i] + rolls[i+1];
                i += 2;
            }
            frames.push_back(frame);
        }


        // Print frame-wise score
        if(f < 10)
        {
        cout<<"Player left before completing the Game --disqualified "<<endl;
        return 0;
        }
        else
        {
        int total = 0;
        cout << "Frame-wise scores:\n";
        for (int f = 0; f < 10; f++) {
            total += frames[f].score;
            cout << "Frame " << f + 1 << ": " << frames[f].score << "\n";
        }
        cout << "-----------------------------\n";
        cout << "Total Score: " << total << "\n";
        return total;
    }
    }
};

int main() {
    BowlingGame game;
    string input;
    int selection;
    char ch= 'Y';
    while(ch == 'Y' || ch == 'y')
    {
    cout<<"Enter number for Manual inputs or run Default unit tests?\n[1]. Manual input  \n[2].Unit tests\n";
    cin>>selection;

    if(1 == selection)
    {
    cout << "Enter bowling scores ( X is strike, / is spare ): ";
    cin >> input;

    try {
        game.scoreGame(input);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }
    }
    else
    {
        runTests();

    }
    cout<<"Play Again??? (y/n)\n";
    cin>>ch;
    }
    return 0;
}

//to perform unit test
void runTests() {
    BowlingGame game;

    // 1. Perfect game
    assert(game.scoreGame("XXXXXXXXXXXX") == 300);

    // 2. All spares (5/5/5/... + 5)
    assert(game.scoreGame("5/5/5/5/5/5/5/5/5/5/5") == 150);

    // 3. All open frames (no bonuses)
    assert(game.scoreGame("12345123451234512345") == 60);

    // 4. Random mixed game
    assert(game.scoreGame("X7/90X088/06XXX81") == 167);

    // 5. No strikes or spares
    assert(game.scoreGame("90909090909090909090") == 90);

    // 6. Incomplete game (should not crash)
    try {
        game.scoreGame("X7/9-");
        cout << "Incomplete game handled.\n";
    } catch (...) {
        cout << "Caught exception for incomplete game.\n";
    }

    // 7. Invalid characters
    try {
        game.scoreGame("X7/9aX-88/-6X");
        assert(false); // This should not be reached
    } catch (const exception& e) {
        cout << "Correctly caught error: " << e.what() << endl;
    }

    cout << "All tests passed.\n";
}

