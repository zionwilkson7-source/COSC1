#include "ArcadeManager.h"
#include <iostream>
using namespace std;

int main() {
    cout << "=======================================" << endl;
    cout << "     CAMPUS GAME ARCADE" << endl;
    cout << "=======================================" << endl << endl;

    ArcadeManager arcade("Student");

    cout << "Welcome! Let's play some games.\n" << endl;

    arcade.launchMenu();

    cout << "\nThanks for playing at the Campus Game Arcade!" << endl;

    return 0;
}

