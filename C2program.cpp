// Programming Assignment 2
// Programming Fundamentals II (COSC 1437)
// Author: Zion
// Description: Calculates weekly summer job pay with tax and bonus.

#include <iostream>
#include <iomanip>      // needed for fixed and setprecision
#include <string>       // Part A: string header

using namespace std;

int main()
{
    // Part B: Named constants
    const double TAX_RATE = 0.14;
    const int BONUS = 50;

    // Part C: Variables
    string name;
    double payRate;
    double hoursWorked;
    double grossPay;
    double tax;
    double netPay;

    // Format all decimal output to two places
    cout << fixed << setprecision(2);

    // Part D: Input
    cout << "Enter last name: ";
    cin >> name;

    cout << "Enter hourly pay rate: ";
    cin >> payRate;

    cout << "Enter hours worked this week: ";
    cin >> hoursWorked;

    // Part E: Calculations
    grossPay = payRate * hoursWorked;
    tax = grossPay * TAX_RATE;
    netPay = grossPay - tax + BONUS;

    // Part F: Formatted Output
    cout << endl;
    cout << "Employee: " << name << endl;
    cout << "Pay Rate: $" << payRate << endl;
    cout << "Hours Worked: " << hoursWorked << endl;
    cout << "Gross Pay: $" << grossPay << endl;
    cout << "Tax (" << static_cast<int>(TAX_RATE * 100) << "%): $" << tax << endl;
    cout << "Net Pay (after tax + $" << BONUS << " bonus): $" << netPay << endl;

    return 0;
}