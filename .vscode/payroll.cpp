#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    ifstream inFile;
    ofstream outFile;

    // C — Open and check files
    inFile.open("payrollData.txt");
    if (!inFile) {
        cout << "Error: Could not open payrollData.txt" << endl;
        return 1;
    }

    outFile.open("payrollReport.txt");
    if (!outFile) {
        cout << "Error: Could not open payrollReport.txt" << endl;
        inFile.close();
        return 1;
    }

    // Set formatting for output
    outFile << fixed << showpoint << setprecision(2);

    string firstName, lastName, department;
    double grossSalary, bonusPercent, taxPercent;
    double distance, travelTime;

    // D — Read structured data in a loop
    while (inFile >> firstName >> lastName >> department) {
        // Read line 2
        inFile >> grossSalary >> bonusPercent >> taxPercent;
        // Read line 3
        inFile >> distance >> travelTime;

        // E — Calculate
        double bonusAmount = grossSalary * bonusPercent / 100.0;
        double taxAmount = grossSalary * taxPercent / 100.0;
        double paycheck = grossSalary + bonusAmount - taxAmount;
        double averageSpeed = (travelTime > 0) ? distance / travelTime : 0.0;

        // F — Write formatted report
        outFile << "Name: " << firstName << " " << lastName 
                << ", Department: " << department << endl;

        outFile << "Monthly Gross Salary: $" << setw(8) << grossSalary 
                << ", Bonus: " << setw(5) << bonusPercent << "%"
                << ", Taxes: " << setw(5) << taxPercent << "%" << endl;

        outFile << "Paycheck: $" << setw(8) << paycheck << endl;

        outFile << "Distance Traveled: " << setw(8) << distance << " miles"
                << ", Travel Time: " << setw(5) << travelTime << " hours" << endl;

        outFile << "Average Speed: " << setw(8) << averageSpeed 
                << " miles per hour" << endl << endl;
    }

    // G — Close files
    inFile.close();
    outFile.close();

    cout << "Payroll report has been generated successfully in payrollReport.txt" << endl;

    return 0;
}