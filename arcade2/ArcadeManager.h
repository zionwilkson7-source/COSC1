#ifndef ARCADEMANAGER_H
#define ARCADEMANAGER_H

#include "SlotMachine.h"
#include "NumberGuesser.h"
#include "WordScramble.h"
#include <iostream>
#include <string>
using namespace std;

class ArcadeManager {
public:
    struct HighScore {
        string playerName;
        int score;
    };

    ArcadeManager(string name = "Player");
    ~ArcadeManager();

    void setPlayer(string name, int tokens);
    void launchMenu();
    void printStats() const;
    void awardBonus(int amount);

    static int totalSessions;
    static void printLeaderboard();

private:
    string playerName;
    int totalTokens;
    string lastGame;
    HighScore leaderboard[5];  // Simple leaderboard

    SlotMachine slots;
    NumberGuesser guesser;
    WordScramble scramble;

    void runSlots();
    void runGuesser();
    void runScramble();
    void updateLeaderboard(int score);
};

#endif