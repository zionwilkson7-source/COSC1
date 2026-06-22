//
// Name: Zion Wilson
// Date: June 21, 2026
// Course: COSC 1437 C++ Programming Fundamentals II
// Desc: Chapter 9 Lab - Student Grade Report System using Records (structs)
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Struct definition
struct studentType 
{
    string studentFName;
    string studentLName;
    int testScore;
    char grade;
};

// Function prototypes
void readStudentsData(ifstream& inFile, studentType roster[], int size);
void assignGrades(studentType roster[], int size);
int findHighestScore(const studentType roster[], int size);
void printHighestScorers(ostream& out, const studentType roster[], int size, int highestScore);
void printGradeReport(ostream& out, const studentType roster[], int size);

int main() 
{
    const int CLASS_SIZE = 20;
    studentType studentRoster[CLASS_SIZE];
    
    // File stream declarations
    ifstream inFile;
    ofstream outFile;
    string inFileName, outFileName;
    
    // Prompt for input file
    cout << "Enter input file name: ";
    cin >> inFileName;
    inFile.open(inFileName);
    if (!inFile) {
        cout << "Error: Cannot open input file " << inFileName << endl;
        return 1;
    }
    
    // Prompt for output file
    cout << "Enter output report file name: ";
    cin >> outFileName;
    outFile.open(outFileName);
    if (!outFile) {
        cout << "Error: Cannot open output file " << outFileName << endl;
        inFile.close();
        return 1;
    }
    
    // Process the data
    readStudentsData(inFile, studentRoster, CLASS_SIZE);
    assignGrades(studentRoster, CLASS_SIZE);
    
    int highest = findHighestScore(studentRoster, CLASS_SIZE);
    
    printGradeReport(outFile, studentRoster, CLASS_SIZE);
    printHighestScorers(outFile, studentRoster, CLASS_SIZE, highest);
    
    // Close files
    inFile.close();
    outFile.close();
    
    cout << "Grade report has been written to " << outFileName << endl;
    
    return 0;
}

// Reads student data from input file
void readStudentsData(ifstream& inFile, studentType roster[], int size)
{
    for (int i = 0; i < size; i++) {
        inFile >> roster[i].studentFName >> roster[i].studentLName >> roster[i].testScore;
    }
}

// Assigns letter grades based on test scores
void assignGrades(studentType roster[], int size)
{
    for (int i = 0; i < size; i++) {
        if (roster[i].testScore >= 90)
            roster[i].grade = 'A';
        else if (roster[i].testScore >= 80)
            roster[i].grade = 'B';
        else if (roster[i].testScore >= 70)
            roster[i].grade = 'C';
        else if (roster[i].testScore >= 60)
            roster[i].grade = 'D';
        else
            roster[i].grade = 'F';
    }
}

// Finds the highest test score in the roster
int findHighestScore(const studentType roster[], int size)
{
    int maxScore = 0;
    for (int i = 0; i < size; i++) {
        if (roster[i].testScore > maxScore) {
            maxScore = roster[i].testScore;
        }
    }
    return maxScore;
}

// Prints students who achieved the highest score
void printHighestScorers(ostream& out, const studentType roster[], int size, int highestScore)
{
    out << "\nHighest Test Score: " << highestScore << endl << endl;
    out << "Students with the Highest Score:" << endl;
    
    for (int i = 0; i < size; i++) {
        if (roster[i].testScore == highestScore) {
            out << "- " << roster[i].studentLName << ", " << roster[i].studentFName << endl;
        }
    }
}

// Prints the formatted grade report
void printGradeReport(ostream& out, const studentType roster[], int size)
{
    out << "---------------------------------------------" << endl;
    out << "            ANNUAL CLASS GRADE REPORT" << endl;
    out << "---------------------------------------------" << endl;
    out << "Student Name" << setw(30) << "Test Score" << setw(10) << "Grade" << endl;
    out << "---------------------------------------------" << endl;
    
    for (int i = 0; i < size; i++) {
        string fullName = roster[i].studentLName + ", " + roster[i].studentFName;
        out << left << setw(30) << fullName 
            << right << setw(8) << roster[i].testScore 
            << setw(10) << roster[i].grade << endl;
    }
    
    out << "---------------------------------------------" << endl;
}