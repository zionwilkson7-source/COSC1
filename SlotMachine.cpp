#include "SlotMachine.h"
#include <cstdlib>
#include <ctime>

SlotMachine::SlotMachine() {
    coins = 100;
    totalSpins = 0;
    srand(time(0));
    cout << "=== Welcome to the Slot Machine! ===" << endl;
    cout << "You start with " << coins << " coins." << endl << endl;
}

SlotMachine::SlotMachine(int startCoins) {
    coins = (startCoins > 0) ? startCoins : 100;
    totalSpins = 0;
    srand(time(0));
    cout << "=== Welcome to the Slot Machine! ===" << endl;
    cout << "You start with " << coins << " coins." << endl << endl;
}

SlotMachine::~SlotMachine() {
    cout << "Thanks for playing! You leave with " << coins << " coins." << endl;
}

void SlotMachine::setCoins(int c) {
    if (c > 0) {
        coins = c;
    }
}

string SlotMachine::randomSymbol() {
    string symbols[5] = {"Cherry", "Bell", "Bar", "7", "Lemon"};
    return symbols[rand() % 5];
}

bool SlotMachine::spin(int bet) {
    if (bet <= 0 || bet > coins) {
        cout << "Error: Bet must be > 0 and <= current coins (" << coins << ")." << endl;
        return false;
    }

    // Generate reels
    for (int i = 0; i < 3; i++) {
        reel[i] = randomSymbol();
    }

    totalSpins++;
    coins -= bet;   // pay the bet

    // Win logic
    bool won = false;
    if (reel[0] == reel[1] && reel[1] == reel[2]) {
        int winnings = bet * 5;
        coins += winnings;
        cout << "🎉 JACKPOT! All three match! You win " << winnings << " coins!" << endl;
        won = true;
    } 
    else if (reel[0] == reel[1] || reel[1] == reel[2] || reel[0] == reel[2]) {
        int winnings = bet * 2;
        coins += winnings;
        cout << "✅ Two matches! You win " << winnings << " coins!" << endl;
        won = true;
    } 
    else {
        cout << "No match. Better luck next time." << endl;
    }

    return won;
}

void SlotMachine::printResult() const {
    cout << "Reels: [" << reel[0] << "] [" << reel[1] << "] [" << reel[2] << "]" << endl;
}

void SlotMachine::resetMachine() {
    coins = 100;
    totalSpins = 0;
    cout << "Slot machine has been reset to default." << endl;
}