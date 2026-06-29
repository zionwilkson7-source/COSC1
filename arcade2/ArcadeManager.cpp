#include "ArcadeManager.h"

int ArcadeManager::totalSessions = 0;

ArcadeManager::ArcadeManager(string name) {
    playerName = name;
    totalTokens = 100;
    lastGame = "None";
    totalSessions++;

    for (int i = 0; i < 10; i++) {
        leaderboard[i].playerName = "";
        leaderboard[i].score = 0;
    }
}

ArcadeManager::~ArcadeManager() {
    cout << "\nThank you for playing at the Campus Arcade, " << playerName << "!" << endl;
}

void ArcadeManager::setPlayer(string name, int tokens) {
    if (!name.empty()) playerName = name;
    if (tokens > 0) totalTokens = tokens;
}

void ArcadeManager::printLeaderboard() {
    cout << "\n=== GLOBAL LEADERBOARD ===\n";
    cout << "1. Alice     - 520\n";
    cout << "2. Bob       - 480\n";
    cout << "3. Charlie   - 410\n";
    cout << "4. Dana      - 390\n";
    cout << "5. Current Player - TBD\n";
}

void ArcadeManager::updateLeaderboard(int score) {
    if (score > leaderboard[9].score) {
        leaderboard[9].playerName = playerName;
        leaderboard[9].score = score;
    }
}

void ArcadeManager::runSlots() {
    int bet;
    cout << "\n--- Slot Machine ---\n";
    cout << "Current coins: " << slots.getCoins() << endl;
    cout << "Enter your bet: ";
    cin >> bet;

    slots.spin(bet);           // Removed unused 'won' variable
    slots.printResult();

    lastGame = "Slot Machine";
}

void ArcadeManager::runGuesser() {
    cout << "\n--- Number Guesser ---\n";
    NumberGuesser::printGamesPlayed();

    int guess;
    string result;
    do {
        cout << "Guess a number (1-100): ";
        cin >> guess;
        result = guesser.guess(guess);
        cout << result << endl;
    } while (result != "Correct!");

    lastGame = "Number Guesser";
}

void ArcadeManager::runScramble() {
    cout << "\n--- Word Scramble ---\n";
    cout << "Scrambled: " << scramble.getScrambled() << endl;
    cout << "Lives remaining: " << scramble.getLivesLeft() << endl;

    string attempt;
    while (scramble.getLivesLeft() > 0) {
        cout << "Your guess: ";
        cin >> attempt;
        if (scramble.tryGuess(attempt)) {
            cout << "Correct! Well done!\n";
            break;
        } else {
            cout << "Wrong! Lives left: " << scramble.getLivesLeft() << endl;
        }
    }

    if (scramble.getLivesLeft() == 0) {
        scramble.reveal();
    }

    lastGame = "Word Scramble";
}

void ArcadeManager::launchMenu() {
    int choice;
    do {
        cout << "\n=== CAMPUS ARCADE ===\n";
        cout << "Player: " << playerName << " | Tokens: " << totalTokens << endl;
        cout << "1. Slot Machine\n";
        cout << "2. Number Guesser\n";
        cout << "3. Word Scramble\n";
        cout << "4. View Stats\n";
        cout << "5. Print Leaderboard\n";
        cout << "6. Quit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: runSlots();    break;
            case 2: runGuesser();  break;
            case 3: runScramble(); break;
            case 4: printStats();  break;
            case 5: printLeaderboard(); break;
            case 6: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option. Try again.\n";
        }
    } while (choice != 6);
}

void ArcadeManager::printStats() const {
    cout << "\n=== Session Statistics ===\n";
    cout << "Player Name     : " << playerName << endl;
    cout << "Last Game Played: " << lastGame << endl;
    cout << "Total Sessions  : " << totalSessions << endl;
    cout << "Current Tokens  : " << totalTokens << endl;
}

void ArcadeManager::awardBonus(int amount) {
    totalTokens += amount;
    cout << "Bonus awarded: +" << amount << " tokens!\n";
}