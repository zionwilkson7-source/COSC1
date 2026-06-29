#include "NumberGuesser.h"

// Static member initialization (required)
int NumberGuesser::gamesPlayed = 0;

NumberGuesser::NumberGuesser(int lo, int hi) {
    srand(time(0));  // Seed random number generator

    if (lo > hi) swap(lo, hi);  // Ensure valid range

    secretNumber = rand() % (hi - lo + 1) + lo;
    maxGuesses = 7;
    guessCount = 0;
    solved = false;

    gamesPlayed++;   // Increment shared static counter
}

NumberGuesser::~NumberGuesser() {
    // Optional cleanup
}

string NumberGuesser::guess(int n) {
    guessCount++;

    if (n == secretNumber) {
        solved = true;
        return "Correct!";
    } else if (n < secretNumber) {
        return "Too Low";
    } else {
        return "Too High";
    }
}

void NumberGuesser::reset() {
    srand(time(0));
    secretNumber = rand() % 100 + 1;  // Default range 1-100
    guessCount = 0;
    solved = false;
    gamesPlayed++;   // Increment on reset (new game)
}

void NumberGuesser::setRange(int lo, int hi) {
    if (lo > hi) swap(lo, hi);
    secretNumber = rand() % (hi - lo + 1) + lo;
}

void NumberGuesser::printGamesPlayed() {
    cout << "Total Number Guesser games played (across all objects): " 
         << gamesPlayed << endl;
}