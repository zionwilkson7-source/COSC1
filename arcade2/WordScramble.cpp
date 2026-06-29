#include "WordScramble.h"

WordScramble::WordScramble() {
    srand(time(0));
    string wordBank[12] = {
        "COMPUTER", "PROGRAMMING", "INHERITANCE", "POLYMORPHISM",
        "ENCAPSULATION", "ABSTRACTION", "OVERLOADING", "TEMPLATE",
        "DYNAMIC", "VIRTUAL", "CONSTRUCTOR", "DESTRUCTOR"
    };
    
    originalWord = wordBank[rand() % 12];
    livesLeft = 5;
    won = false;
    scramble();
}

WordScramble::WordScramble(string word, int lives) {
    srand(time(0));
    originalWord = word;
    livesLeft = (lives > 0) ? lives : 5;
    won = false;
    scramble();
}

WordScramble::~WordScramble() {
    cout << "Thanks for playing Word Scramble!" << endl;
}

// Private helper - only called internally
void WordScramble::scramble() {
    scrambled = originalWord;
    int n = scrambled.length();
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(scrambled[i], scrambled[j]);
    }
    // Retry if shuffle resulted in same word
    if (scrambled == originalWord && n > 1) {
        scramble();
    }
}

void WordScramble::setWord(string word) {
    originalWord = word;
    livesLeft = 5;
    won = false;
    scramble();
}

bool WordScramble::tryGuess(string attempt) {
    if (attempt == originalWord) {
        won = true;
        return true;
    }
    
    livesLeft--;
    return false;
}

string WordScramble::getScrambled() const {
    return scrambled;
}

int WordScramble::getLivesLeft() const {
    return livesLeft;
}

void WordScramble::reveal() const {
    cout << "The original word was: " << originalWord << endl;
}