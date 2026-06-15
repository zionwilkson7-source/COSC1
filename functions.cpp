#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

// ====================== PART 1 ======================
/**
 * mathSummary - Displays mathematical summary using predefined <cmath> functions
 * @param x - the number to analyze
 */
void mathSummary(double x) {
    cout << "\n--- Math Summary for " << x << " ---" << endl;
    cout << "Square root: " << sqrt(x) << endl;
    cout << "Raised to power 3: " << pow(x, 3) << endl;
    cout << "Ceiling: " << ceil(x) << endl;
    cout << "Floor: " << floor(x) << endl;
    cout << "Absolute value of x * -1: " << abs(x * -1) << endl;
}

// ====================== PART 2 ======================
/**
 * calcTax - Calculates tax owed based on income and tax rate
 * @param income - gross income
 * @param rate - tax rate as decimal (e.g., 0.25 for 25%)
 * @return tax owed (income * rate)
 */
double calcTax(double income, double rate);

// ====================== PART 3 ======================
/**
 * printHeader - Prints a formatted header with course title
 * @param courseTitle - title to display in header
 */
void printHeader(string courseTitle);

/**
 * displayResult - Displays a labeled numeric result formatted to 2 decimal places
 * @param label - description text
 * @param value - numeric value to display
 */
void displayResult(string label, double value);

// ====================== PART 4 ======================
/**
 * convertTime - Converts total seconds into minutes and remaining seconds
 * @param totalSeconds - total seconds (passed by value)
 * @param minutes - output parameter for whole minutes (passed by reference)
 * @param seconds - output parameter for remaining seconds (passed by reference)
 */
void convertTime(int totalSeconds, int& minutes, int& seconds);

// ====================== PART 5 ======================
/**
 * countCalls - Demonstrates static local variable by tracking call count
 * Static variables retain their value between function calls, unlike regular
 * local variables which are reinitialized each time.
 */
void countCalls();

// ====================== PART 6 ======================
/**
 * displayBox - Draws a square box outline using * characters (overloaded version)
 * @param width - width and height of the square
 */
void displayBox(int width);

/**
 * displayBox - Draws a rectangular box outline using * characters (overloaded version)
 * @param width - width of the box
 * @param height - height of the box
 */
void displayBox(int width, int height);

// ====================== PART 7 ======================
/**
 * calcShipping - Calculates total shipping cost
 * @param weight - package weight in pounds
 * @param ratePerPound - shipping rate per pound (default 1.50)
 * @param baseFee - base shipping fee (default 5.00)
 * @return total shipping cost
 */
double calcShipping(double weight, double ratePerPound = 1.50, double baseFee = 5.00);

int main() {
    cout << fixed << setprecision(2);

    // Part 1: Predefined Functions
    cout << "=== PART 1: Predefined Math Functions ===" << endl;
    mathSummary(16.75);
    mathSummary(-9.3);
    mathSummary(0.0);

    // Part 2: Value-Returning Function + Part 3: Void Functions
    cout << "\n=== PART 2 & 3: Tax Calculation ===" << endl;
    double income, rate;
    cout << "Enter gross income: ";
    cin >> income;
    cout << "Enter tax rate (as decimal, e.g. 0.25): ";
    cin >> rate;

    double tax = calcTax(income, rate);

    printHeader("C++ Programming - Tax Calculator");
    displayResult("Gross Income", income);
    displayResult("Tax Rate", rate);
    displayResult("Tax Owed", tax);

    // Part 4: Value vs Reference Parameters
    cout << "\n=== PART 4: Time Conversion (Value vs Reference) ===" << endl;
    int totalSeconds, minutes, seconds;
    cout << "Enter total seconds: ";
    cin >> totalSeconds;
    
    convertTime(totalSeconds, minutes, seconds);
    printHeader("Time Conversion Result");
    displayResult("Minutes", minutes);
    displayResult("Seconds", seconds);
    // Note: minutes and seconds must be reference parameters because we need
    // the function to modify the caller's variables with the computed values.

    // Part 5: Static Variables
    cout << "\n=== PART 5: Static Variable Demo ===" << endl;
    countCalls();
    countCalls();
    countCalls();
    countCalls();
    countCalls();

    // Part 6: Function Overloading
    cout << "\n=== PART 6: Function Overloading - Box Display ===" << endl;
    displayBox(5);           // Square
    cout << endl;
    displayBox(8, 4);        // Rectangle

    // Part 7: Default Parameters
    cout << "\n=== PART 7: Default Parameters - Shipping Cost ===" << endl;
    double w1 = 10.5, w2 = 3.0, w3 = 15.75;
    
    cout << "Shipping for " << w1 << " lbs (all args): $" 
         << calcShipping(w1, 2.25, 8.00) << endl;
    
    cout << "Shipping for " << w2 << " lbs (weight + rate): $" 
         << calcShipping(w2, 1.75) << endl;
    
    cout << "Shipping for " << w3 << " lbs (only weight): $" 
         << calcShipping(w3) << endl;

    return 0;
}

// ====================== FUNCTION IMPLEMENTATIONS ======================

double calcTax(double income, double rate) {
    return income * rate;
}

void printHeader(string courseTitle) {
    const int WIDTH = 50;
    string border(WIDTH, '-');
    
    cout << border << endl;
    cout << "| " << courseTitle;
    // Center the title
    int padding = WIDTH - courseTitle.length() - 3;
    cout << string(padding / 2, ' ') << " |" << endl;
    cout << border << endl;
}

void displayResult(string label, double value) {
    cout << left << setw(20) << label << ": $" << value << endl;
}

void convertTime(int totalSeconds, int& minutes, int& seconds) {
    minutes = totalSeconds / 60;
    seconds = totalSeconds % 60;
}

void countCalls() {
    static int callCount = 0;
    callCount++;
    cout << "countCalls has been called " << callCount << " time(s)." << endl;
}

void displayBox(int width) {
    // Top
    for (int i = 0; i < width; i++) cout << "*";
    cout << endl;
    
    // Middle
    for (int i = 1; i < width - 1; i++) {
        cout << "*";
        for (int j = 1; j < width - 1; j++) cout << " ";
        cout << "*" << endl;
    }
    
    // Bottom
    for (int i = 0; i < width; i++) cout << "*";
    cout << endl;
}

void displayBox(int width, int height) {
    if (height < 1 || width < 1) return;
    
    // Top
    for (int i = 0; i < width; i++) cout << "*";
    cout << endl;
    
    // Middle rows
    for (int i = 1; i < height - 1; i++) {
        cout << "*";
        for (int j = 1; j < width - 1; j++) cout << " ";
        cout << "*" << endl;
    }
    
    // Bottom
    if (height > 1) {
        for (int i = 0; i < width; i++) cout << "*";
        cout << endl;
    }
}

double calcShipping(double weight, double ratePerPound, double baseFee) {
    return baseFee + (weight * ratePerPound);
}