// ============================================================
// COSC 1437 - Chapter 11: Inheritance and Composition
// Animal Shelter System
//
// Name: Zion Wilson
// Date: June 27, 2026
// ============================================================
#include <iostream>
#include <string>
using namespace std;

// ============================================================
// CLASS: Address (used for composition in Shelter)
// This class is fully implemented. Study it.
// ============================================================
class Address
{
public:
    void setAddress(string street, string city, string state);
    void printAddress() const;
    Address(string street = "", string city = "", string state = "");
private:
    string street;
    string city;
    string state;
};
void Address::setAddress(string s, string c, string st)
{
    street = s;
    city = c;
    state = st;
}
void Address::printAddress() const
{
    cout << street << ", " << city << ", " << state;
}
Address::Address(string s, string c, string st)
{
    street = s;
    city = c;
    state = st;
}

// ============================================================
// CLASS: Animal (BASE CLASS)
// ============================================================
class Animal
{
public:
    void setInfo(string n, int a, string t);
    string getName() const;
    int getAge() const;
    string getType() const;
    void print() const;
    Animal(string n = "", int a = 0, string t = "");
protected:
    string name;
    int age;
    string animalType;
};

// Animal Member Function Definitions
Animal::Animal(string n, int a, string t)
{
    name = n;
    age = a;
    animalType = t;
}

void Animal::setInfo(string n, int a, string t)
{
    name = n;
    age = a;
    animalType = t;
}

string Animal::getName() const
{
    return name;
}

int Animal::getAge() const
{
    return age;
}

string Animal::getType() const
{
    return animalType;
}

void Animal::print() const
{
    cout << "Name: " << name 
         << "  Age: " << age 
         << "  Type: " << animalType << endl;
}

// ============================================================
// CLASS: Dog (DERIVED from Animal)
// ============================================================
class Dog : public Animal
{
public:
    void setBreed(string b);
    string getBreed() const;
    void print() const;
    Dog(string name = "", int age = 0, string breed = "");
private:
    string breed;
};

// Dog Member Function Definitions
Dog::Dog(string n, int a, string b) : Animal(n, a, "Dog")
{
    breed = b;
}

void Dog::setBreed(string b)
{
    breed = b;
}

string Dog::getBreed() const
{
    return breed;
}

void Dog::print() const
{
    Animal::print();                    // Call base class print first
    cout << "Breed: " << breed << endl;
}

// ============================================================
// CLASS: Cat (DERIVED from Animal)
// ============================================================
class Cat : public Animal
{
public:
    void setIndoor(bool i);
    bool getIndoor() const;
    void print() const;
    Cat(string name = "", int age = 0, bool indoor = true);
private:
    bool isIndoor;
};

// Cat Member Function Definitions
Cat::Cat(string n, int a, bool indoor) : Animal(n, a, "Cat")
{
    isIndoor = indoor;
}

void Cat::setIndoor(bool i)
{
    isIndoor = i;
}

bool Cat::getIndoor() const
{
    return isIndoor;
}

void Cat::print() const
{
    Animal::print();                    // Call base class print first
    cout << "Indoor: " << (isIndoor ? "Yes" : "No") << endl;
}

// ============================================================
// CLASS: Shelter (COMPOSITION demo)
// ============================================================
class Shelter
{
public:
    void printInfo() const;
    Shelter(string name, string street, string city,
            string state, int cap);
private:
    string shelterName;
    Address location; // composition: Shelter HAS-A Address
    int capacity;
};

void Shelter::printInfo() const
{
    cout << "Shelter: " << shelterName << endl;
    cout << "Address: ";
    location.printAddress();
    cout << endl;
    cout << "Capacity: " << capacity << " animals" << endl;
}

// Shelter Constructor
Shelter::Shelter(string name, string street, string city,
                 string state, int cap)
    : location(street, city, state)
{
    shelterName = name;
    capacity = cap;
}

// ============================================================
// MAIN (do not modify)
// ============================================================
int main()
{
    cout << "=== Animal Shelter System ===" << endl << endl;
    // PART 1: Shelter (composition)
    cout << "--- Shelter Info ---" << endl;
    Shelter happyPaws("Happy Paws Shelter",
                      "123 Main St", "Humble", "TX", 50);
    happyPaws.printInfo();
    cout << endl;

    // PART 2: Base class
    cout << "--- Base Class Animals ---" << endl;
    Animal a1("Generic", 4, "Unknown");
    a1.print();
    cout << endl;

    Animal a2;
    a2.setInfo("Another", 2, "Mystery");
    a2.print();
    cout << endl;

    // PART 3: Dogs (inheritance + override)
    cout << "--- Dogs ---" << endl;
    Dog d1("Buddy", 3, "Labrador");
    d1.print();
    cout << endl;

    Dog d2;
    d2.setInfo("Max", 5, "Dog");
    d2.setBreed("Beagle");
    d2.print();
    cout << endl;

    // PART 4: Cats (inheritance + override)
    cout << "--- Cats ---" << endl;
    Cat c1("Whiskers", 5, true);
    c1.print();
    cout << endl;

    Cat c2("Shadow", 2, false);
    c2.print();
    cout << endl;

    // PART 5: IS-A demo using Animal array
    cout << "--- All Animals in Shelter ---" << endl;
    Animal* roster[4];
    roster[0] = &a1;
    roster[1] = &d1;
    roster[2] = &c1;
    roster[3] = &c2;

    for (int i = 0; i < 4; i++)
    {
        cout << "Animal " << i + 1 << ": "
             << roster[i]->getName()
             << " (" << roster[i]->getType() << ")"
             << " - Age: " << roster[i]->getAge() << endl;
    }

    cout << endl << "Program complete." << endl;
    return 0;
}