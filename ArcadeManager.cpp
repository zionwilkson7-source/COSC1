#include "ArcadeManager.h"

int ArcadeManager::totalSessions = 0;

ArcadeManager::ArcadeManager(string name) {
    playerName = name;
    totalTokens = 100;
    lastGame = "None";
    totalSessions++;
    for (int i = 0; i < 5; i++) {
        leaderboard[i].score = 0;
    }
}

ArcadeManager::~ArcadeManager() {
    cout << "\nThanks for playing at the Campus Arcade, " << playerName << "!" << endl;
}

void ArcadeManager::setPlayer(string name, int tokens) {
    playerName = name;
    totalTokens = tokens;
}

void ArcadeManager::printLeaderboard() {
    cout << "\n=== GLOBAL LEADERBOARD ===\n";
    // Static demo scores
    cout << "1. Alice - 450\n";
    cout << "2. Bob - 380\n";
    cout << "3. " << "Current Player" << " - " << "TBD\n";
}

void ArcadeManager::updateLeaderboard(int score) {
    // Simple update (demo)
    if (score > leaderboard[4].score) {
        leaderboard[4].playerName = playerName;
        leaderboard[4].score = score;
    }
}

void ArcadeManager::runSlots() {
    int bet;
    cout << "\n--- Slot Machine ---\n";
    cout << "You have " << slots.getCoins() << " coins.\n";
    cout << "Enter bet: ";
    cin >> bet;
    bool won = slots.spin(bet);
    slots.printResult();
    lastGame = "Slots";
}

void ArcadeManager::runGuesser() {
    cout << "\n--- Number Guesser ---\n";
    NumberGuesser::printGamesPlayed();
    int guess;
    string result;
    do {
        cout << "Guess the number (1-100): ";
        cin >> guess;
        result = guesser.guess(guess);
        cout << result << endl;
    } while (result != "Correct!");
    lastGame = "Number Guesser";
}

void ArcadeManager::runScramble() {
    cout << "\n--- Word Scramble ---\n";
    cout << "Scrambled word: " << scramble.getScrambled() << endl;
    cout << "Lives: " << scramble.getLivesLeft() << endl;

    string attempt;
    while (scramble.getLivesLeft() > 0) {
        cout << "Your guess: ";
        cin >> attempt;
        if (scramble.tryGuess(attempt)) {
            cout << "You got it!\n";
            break;
        } else {
            cout << "Wrong! Lives left: " << scramble.getLivesLeft() << endl;
        }
    }
    if (scramble.getLivesLeft() == 0) scramble.reveal();
    lastGame = "Word Scramble";
}

void ArcadeManager::launchMenu() {
    int choice;
    do {
        cout << "\n=== CAMPUS GAME ARCADE ===\n";
        cout << "Player: " << playerName << " | Tokens: " << totalTokens << endl;
        cout << "1. Slot Machine\n";
        cout << "2. Number Guesser\n";
        cout << "3. Word Scramble\n";
        cout << "4. View Stats\n";
        cout << "5. Print Leaderboard\n";
        cout << "6. Quit\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1: runSlots(); break;
            case 2: runGuesser(); break;
            case 3: runScramble(); break;
            case 4: printStats(); break;
            case 5: printLeaderboard(); break;
            case 6: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);
}

void ArcadeManager::printStats() const {
    cout << "\n=== Session Stats ===\n";
    cout << "Player: " << playerName << endl;
    cout << "Last Game: " << lastGame << endl;
    cout << "Total Sessions: " << totalSessions << endl;
}

void ArcadeManager::awardBonus(int amount) {
    totalTokens += amount;
    cout << "Bonus awarded: +" << amount << " tokens!\n";
}