// ========================================================
// Programming Assignment #2 - Car Dealership Inventory
// ========================================================
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

// =========================================================
// Base Class: Vehicle
// =========================================================
class Vehicle {
private:
    string make;
    string model;
    string color;
    int mpg;
    double msrp;

public:
    // Constructor
    Vehicle(string mk, string md, string col, int m, double price)
        : make(mk), model(md), color(col), mpg(m), msrp(price) {}

    // Getters
    string getMake() const { return make; }
    string getModel() const { return model; }
    string getColor() const { return color; }
    int getMpg() const { return mpg; }
    double getMsrp() const { return msrp; }

    // Virtual destructor and print function for polymorphism
    virtual ~Vehicle() {}
    virtual void print() const {
        cout << left << setw(12) << make << setw(12) << model << setw(10) << color
             << setw(6) << mpg << " mpg   $" << fixed << setprecision(2) << msrp;
    }

    virtual string getType() const { return "Vehicle"; }
};

// =========================================================
// Derived Class: Car
// =========================================================
class Car : public Vehicle {
private:
    bool spareInTrunk;
    bool rearWindshieldWiper;

public:
    Car(string mk, string md, string col, int m, double price, bool spare, bool wiper)
        : Vehicle(mk, md, col, m, price), spareInTrunk(spare), rearWindshieldWiper(wiper) {}

    void print() const override {
        Vehicle::print();
        cout << "   Car   Spare: " << (spareInTrunk ? "Yes" : "No")
             << "   Wiper: " << (rearWindshieldWiper ? "Yes" : "No") << endl;
    }

    string getType() const override { return "Car"; }
};

// =========================================================
// Derived Class: Truck
// =========================================================
class Truck : public Vehicle {
private:
    bool sidePanelStorage;
    bool autoReleaseTailgate;

public:
    Truck(string mk, string md, string col, int m, double price, bool side, bool tailgate)
        : Vehicle(mk, md, col, m, price), sidePanelStorage(side), autoReleaseTailgate(tailgate) {}

    void print() const override {
        Vehicle::print();
        cout << "   Truck   Side Storage: " << (sidePanelStorage ? "Yes" : "No")
             << "   Auto Tailgate: " << (autoReleaseTailgate ? "Yes" : "No") << endl;
    }

    string getType() const override { return "Truck"; }
};

// =========================================================
// Main Program
// =========================================================
vector<Vehicle*> inventory;

void loadInventory(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Warning: Could not open file " << filename << ". Starting with empty inventory.\n";
        return;
    }

    string type, make, model, color;
    int mpg;
    double msrp;
    bool flag1, flag2;

    while (file >> type) {
        file >> make >> model >> color >> mpg >> msrp >> flag1 >> flag2;
        if (type == "Car") {
            inventory.push_back(new Car(make, model, color, mpg, msrp, flag1, flag2));
        } else if (type == "Truck") {
            inventory.push_back(new Truck(make, model, color, mpg, msrp, flag1, flag2));
        }
    }
    file.close();
    cout << "Loaded " << inventory.size() << " vehicles from file.\n";
}

void addVehicle() {
    string choice;
    cout << "Add (Car) or (Truck)? ";
    cin >> choice;

    string make, model, color;
    int mpg;
    double msrp;
    bool flag1, flag2;

    cout << "Enter make: "; cin >> make;
    cout << "Enter model: "; cin >> model;
    cout << "Enter color: "; cin >> color;
    cout << "Enter MPG: "; cin >> mpg;
    cout << "Enter MSRP: $"; cin >> msrp;

    if (choice == "Car" || choice == "car") {
        cout << "Spare tire in trunk? (1=Yes, 0=No): "; cin >> flag1;
        cout << "Rear windshield wiper? (1=Yes, 0=No): "; cin >> flag2;
        inventory.push_back(new Car(make, model, color, mpg, msrp, flag1, flag2));
    } else {
        cout << "Side panel storage? (1=Yes, 0=No): "; cin >> flag1;
        cout << "Auto release tailgate? (1=Yes, 0=No): "; cin >> flag2;
        inventory.push_back(new Truck(make, model, color, mpg, msrp, flag1, flag2));
    }
    cout << "Vehicle added successfully!\n";
}

void printInventory() {
    if (inventory.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }
    cout << "\n=== Current Inventory ===\n";
    for (size_t i = 0; i < inventory.size(); i++) {
        cout << i + 1 << ". ";
        inventory[i]->print();
    }
    cout << endl;
}

void searchVehicles() {
    string category, value;
    cout << "Search by (make/model/color): ";
    cin >> category;
    cout << "Enter " << category << ": ";
    cin >> value;

    cout << "\nSearch Results:\n";
    bool found = false;
    for (Vehicle* v : inventory) {
        if ((category == "make" || category == "Make") && v->getMake() == value) {
            v->print();
            found = true;
        } else if ((category == "model" || category == "Model") && v->getModel() == value) {
            v->print();
            found = true;
        } else if ((category == "color" || category == "Color") && v->getColor() == value) {
            v->print();
            found = true;
        }
    }
    if (!found) cout << "No matching vehicles found.\n";
}

void printDetails() {
    if (inventory.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }
    int index;
    cout << "Enter vehicle number (1 to " << inventory.size() << "): ";
    cin >> index;
    if (index < 1 || index > (int)inventory.size()) {
        cout << "Invalid number.\n";
        return;
    }
    cout << "\n=== Detailed Information ===\n";
    inventory[index - 1]->print();
    cout << endl;
}

int main() {
    string filename = "inventory.txt";
    loadInventory(filename);

    int choice;
    do {
        cout << "\n=== Car Dealership Inventory System ===\n";
        cout << "1. Add a vehicle (Car or Truck)\n";
        cout << "2. Print current inventory\n";
        cout << "3. Search vehicles (by make/model/color)\n";
        cout << "4. Print details of a specific vehicle\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addVehicle(); break;
            case 2: printInventory(); break;
            case 3: searchVehicles(); break;
            case 4: printDetails(); break;
            case 5: cout << "Thank you! Exiting program.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    // Clean up memory
    for (Vehicle* v : inventory) {
        delete v;
    }
    return 0;
}