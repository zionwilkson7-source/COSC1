#include "ArcadeManager.h"
#include <iostream>
using namespace std;

int main() {
    cout << "=====================================" << endl;
    cout << "   Welcome to Campus Game Arcade!" << endl;
    cout << "=====================================" << endl << endl;

    ArcadeManager arcade("YourName");

    arcade.launchMenu();

    cout << "\n=== Thanks for playing! ===" << endl;

    return 0;
}