//
// Name: Zion Wilson
// Date: June 18, 2026
// Course: COSC 1437 C++ Programming Fundamentals II
// Desc: Chapter 7 Lab - Student Course Enrollment System
//

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// PART 4: Namespace definition
namespace EnrollmentSystem
{
    // PART 1: Define the courseType enum here.
    // Also declare a variable currentCourse of type courseType in the same statement.
    enum courseType { ENGLISH, MATH, HISTORY, CPP, BIOLOGY, ART } currentCourse;

    // PART 2: typedef aliases
    typedef int StudentID;
    typedef double CreditHours;

    // Function prototypes
    void printCourse(courseType c);
    courseType readCourse();
    double calcTuition(CreditHours credits);
    void printStudentInfo(string fullName, string email, courseType course, StudentID id, CreditHours credits);
}

using namespace EnrollmentSystem;

// PART 1b: printCourse
void EnrollmentSystem::printCourse(courseType c)
{
    switch (c)
    {
        case ENGLISH:
            cout << "English Composition";
            break;
        case MATH:
            cout << "College Algebra";
            break;
        case HISTORY:
            cout << "U.S. History";
            break;
        case CPP:
            cout << "C++ Programming";
            break;
        case BIOLOGY:
            cout << "General Biology";
            break;
        case ART:
            cout << "Art Appreciation";
            break;
        default:
            cout << "Unknown Course";
    }
}

// PART 1c: readCourse
EnrollmentSystem::courseType EnrollmentSystem::readCourse()
{
    string input;
    cout << "Enter course (english/math/history/cpp/biology/art): ";
    cin >> input;
    // Convert to lowercase for robustness, but per spec use direct compare
    if (input == "english" || input == "English")
        return ENGLISH;
    else if (input == "math" || input == "Math")
        return MATH;
    else if (input == "history" || input == "History")
        return HISTORY;
    else if (input == "cpp" || input == "CPP")
        return CPP;
    else if (input == "biology" || input == "Biology")
        return BIOLOGY;
    else if (input == "art" || input == "Art")
        return ART;
    else
    {
        cout << "Invalid course. Defaulting to ENGLISH." << endl;
        return ENGLISH;
    }
}

// PART 2: calcTuition
double EnrollmentSystem::calcTuition(CreditHours credits)
{
    return credits * 150.0;
}

// PART 3b: printStudentInfo
void EnrollmentSystem::printStudentInfo(string fullName, string email, courseType course, StudentID id, CreditHours credits)
{
    cout << endl << "--- Enrollment Summary ---" << endl;
    cout << "Student Name: " << fullName << endl;
    cout << "Student ID: " << id << endl;
    cout << "Email: " << email << endl;
    cout << "Course: ";
    EnrollmentSystem::printCourse(course);
    cout << endl;
    cout << "Credit Hours: " << credits << endl;
    cout << fixed << setprecision(2);
    cout << "Tuition: $" << EnrollmentSystem::calcTuition(credits) << endl;
}

int main()
{
    // --- Welcome banner (use string concatenation) ---
    string line = "=====================================";
    string welcome = line + "\n     STUDENT COURSE ENROLLMENT SYSTEM\n" + line;
    cout << welcome << endl << endl;

    // --- PART 3: String operations ---
    string firstName, lastName, fullName;
    string emailUser, email;

    cout << "Enter first name: ";
    cin >> firstName;
    cout << "Enter last name: ";
    cin >> lastName;

    // TODO 1: Concatenation
    fullName = firstName + " " + lastName;
    cout << "Full name: " << fullName << endl;

    // TODO 2: length()
    cout << "Full name length: " << fullName.length() << " characters" << endl;

    // TODO 3: substr using find
    size_t spacePos = fullName.find(" ");
    if (spacePos != string::npos)
    {
        string firstOnly = fullName.substr(0, spacePos);
        cout << "First name only (substr): " << firstOnly << endl;
    }

    // TODO 4: at() or []
    if (!fullName.empty())
        cout << "First initial: " << fullName[0] << endl;

    // TODO 5: find(' ')
    cout << "Space position: " << fullName.find(' ') << endl;

    cout << "Enter email username (e.g. jsmith): ";
    cin >> emailUser;

    // TODO 6: empty()
    if (emailUser.empty())
    {
        cout << "Email username is empty." << endl;
        email = "";
    }
    else
    {
        // TODO 7: insert
        email = emailUser;
        email.insert(email.length(), "@sanjac.edu");
        cout << "Email after insert: " << email << endl;

        // TODO 8: replace
        size_t sanPos = email.find("sanjac");
        if (sanPos != string::npos)
        {
            email.replace(sanPos, 6, "SanJac");
        }
        cout << "Email after replace: " << email << endl;

        // TODO 9: erase (demo trailing punctuation)
        if (!email.empty() && (email.back() == '.' || email.back() == ','))
        {
            email.erase(email.length() - 1, 1);
        }
        cout << "Email after erase: " << email << endl;
    }

    // TODO 10: compare
    string lastName2 = "Smith";
    int cmp = lastName.compare(lastName2);
    cout << "Comparing last names: " << lastName << " vs " << lastName2 << endl;
    if (cmp < 0)
        cout << lastName << " comes before " << lastName2 << " alphabetically." << endl;
    else if (cmp > 0)
        cout << lastName << " comes after " << lastName2 << " alphabetically." << endl;
    else
        cout << "Last names are the same." << endl;

    // --- PART 1: Enum operations ---
    currentCourse = readCourse();
    cout << "You selected: ";
    printCourse(currentCourse);
    cout << endl;

    // Advance currentCourse by one using static_cast
    if (currentCourse < ART)
    {
        currentCourse = static_cast<courseType>(currentCourse + 1);
        cout << "Advanced course: ";
        printCourse(currentCourse);
        cout << endl;
    }

    // for loop print all courses
    cout << "\nAll available courses:" << endl;
    for (courseType c = ENGLISH; c <= ART; c = static_cast<courseType>(c + 1))
    {
        printCourse(c);
        cout << endl;
    }

    // Compare two courseType
    courseType courseA = MATH;
    courseType courseB = HISTORY;
    if (courseA < courseB)
        cout << "MATH comes before HISTORY in the list." << endl;
    else
        cout << "HISTORY comes before MATH in the list." << endl;

    // --- PART 2: Tuition ---
    CreditHours hours;
    StudentID sid = 10045; // demo student ID
    cout << "\nEnter credit hours: ";
    cin >> hours;
    double tuition = calcTuition(hours);
    cout << "Tuition for " << hours << " credits: $" << fixed << setprecision(2) << tuition << endl;

    // --- Summary ---
    printStudentInfo(fullName, email, currentCourse, sid, hours);

    // PART 4 DEMO: Access one namespace member with full prefix
    // Using full scope resolution as required
    EnrollmentSystem::StudentID demoID = 99999; // Full qualification example
    cout << "\nDemo full namespace access: StudentID = " << demoID << endl;

    return 0;
}