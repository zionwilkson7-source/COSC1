#ifndef WORDSCRAMBLE_H
#define WORDSCRAMBLE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class WordScramble {
public:
    WordScramble();                          // Default constructor - random word from bank
    WordScramble(string word, int lives = 5); // Parametrized constructor

    ~WordScramble();

    void setWord(string word);               // Mutator
    bool tryGuess(string attempt);           // Mutator - main game logic
    string getScrambled() const;             // Accessor
    int getLivesLeft() const;                // Accessor
    void reveal() const;                     // Accessor - shows answer only at end

private:
    string originalWord;
    string scrambled;
    int livesLeft;
    bool won;

    void scramble();   // Private helper - Fisher-Yates shuffle
};

#endif