#ifndef NUMBERGUESSER_H
#define NUMBERGUESSER_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class NumberGuesser {
public:
    NumberGuesser(int lo = 1, int hi = 100);
    ~NumberGuesser();

    string guess(int n);           // Main game logic
    void reset();                  // Reset for new game
    void setRange(int lo, int hi);

    // Inline accessor functions (as required)
    int getGuessCount() const { return guessCount; }
    bool isSolved() const { return solved; }

    // Static members
    static int gamesPlayed;
    static void printGamesPlayed();

private:
    int secretNumber;
    int maxGuesses;
    int guessCount;
    bool solved;
};

#endif