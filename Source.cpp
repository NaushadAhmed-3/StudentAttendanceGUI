#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdlib>
using namespace std;

const int MAX_STUDENTS = 50;
const int MAX_DAYS = 30;

string names[MAX_STUDENTS];
int ids[MAX_STUDENTS];
char attendance[MAX_STUDENTS][MAX_DAYS];
int studentCount = 0, dayCount = 0;
 
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Error: Maximum Student Capacity reached\n";
        return;
    }

    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, names[studentCount]);

    cout << "Enter ID (Numbers only): ";


    if (!(cin >> ids[studentCount])) {
        exit(0); 
    }

    studentCount++;
    cout << "\n!Student added successfully in the system!\n";
    cout << "Total student Entered: " << studentCount << endl;
}

void markAttendance() {
    if (studentCount == 0) {
        cout << " No students have been added yet!\n";
        return;
    }

    int day;
    cout << "--- MARK ATTENDANCE ---\n";
    cout << "Enter day number (1-30): ";
    cin >> day;

    if (day < 1 || day > MAX_DAYS) {
        cout << "Invalid day! Please enter between 1 and " << MAX_DAYS << endl;
        return;
    }

    if (day > dayCount + 1) {
        cout << "WARNING! You are marking day " << day
            << " but previous days have not been marked\n";
    }

    cout << "Marking attendance for Day " << day << endl;
    cout << "Enter 'P' for Present, 'A' for Absent\n";

    char status;
    for (int i = 0; i < studentCount; i++) {
        cout << i + 1 << ". " << names[i]
            << "  ID: " << ids[i] << "  : ";
        cin >> status;
        attendance[i][day - 1] = (toupper(status) == 'P');
    }

    if (day > dayCount) {
        dayCount = day;
    }

    cout << "Attendance for Day " << day << " marked successfully!\n";
}

void displayRecords() {
    if (studentCount == 0) {
        cout << " No students added yet!\n";
        return;
    }

    if (dayCount == 0) {
        cout << "No attendance marked yet!\n";
        return;
    }

    cout << "--- ALL ATTENDANCE RECORDS ---\n\n";

    cout << setw(20) << "Name";
    cout << setw(15) << "ID";
    for (int day = 0; day < dayCount; day++) {
        string header = "D" + to_string(day + 1);
        cout << setw(5) << header;
    }
    cout << endl;

    for (int i = 0; i < studentCount; i++) {
        cout << setw(20) << names[i];
        cout << setw(15) << ids[i];

        for (int day = 0; day < dayCount; day++) {
            cout << setw(5) << (attendance[i][day] ? "P" : "A");
        }
        cout << endl;
    }
}

void updateAttendance() {
    if (studentCount == 0) {
        cout << "   No students added yet!\n";
        return;
    }

    if (dayCount == 0) {
        cout << " No attendance marked yet!\n";
        return;
    }

    int searchID;
    int day;

    cout << "  --- EDIT ATTENDANCE RECORD ---\n";
    cout << "Enter student ID: ";

    if (!(cin >> searchID)) {
        exit(0);
    }

    int foundIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (ids[i] == searchID) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        cout << "Student with ID :" << searchID << " not found!\n";
        return;
    }

    cout << "Enter day number to edit (1-" << dayCount << "): ";
    cin >> day;

    if (day < 1 || day > dayCount) {
        cout << "Invalid day! Only days 1-" << dayCount << " have been marked\n";
        return;
    }

    cout << "\nStudent: " << names[foundIndex]
        << "  ID: " << ids[foundIndex] << endl;
    cout << "Day " << day << " currently: "
        << (attendance[foundIndex][day - 1] ? "Present" : "Absent") << endl;

    char newStatus;
    cout << "Enter new status (P for Present, A for Absent): ";
    cin >> newStatus;

    attendance[foundIndex][day - 1] = (toupper(newStatus) == 'P');

    cout << "\nAttendance record updated successfully!\n";
}

void displayStats() {
    if (studentCount == 0) {
        cout << " No students added yet!\n";
        return;
    }

    if (dayCount == 0) {
        cout << " No attendance marked yet!\n";
        return;
    }

    cout << "*** INDIVIDUAL STUDENT RECORDS ***\n";
    cout << left;
    cout << setw(20) << "STUDENT NAME" << "| ";
    cout << setw(15) << "STUDENT ID" << "| ";
    cout << setw(10) << "PRESENT" << "| ";
    cout << setw(12) << "TOTAL DAYS" << "| ";
    cout << setw(12) << "PERCENTAGE" << "| ";
    cout << "STATUS" << endl;

    for (int i = 0; i < studentCount; i++) {
        int presentCount = 0;
        for (int day = 0; day < dayCount; day++) {
            if (attendance[i][day]) presentCount++;
        }

        double percentage = (dayCount > 0) ? (presentCount * 100.0 / dayCount) : 0.0;

        cout << setw(20) << names[i] << "| ";
        cout << setw(15) << ids[i] << "| ";
        cout << setw(10) << presentCount << "| ";
        cout << setw(12) << dayCount << "| ";

        stringstream ss;
        ss << fixed << setprecision(1) << percentage << "%";
        cout << setw(12) << ss.str() << "| ";

        if (presentCount == dayCount) {
            cout << "PERFECT ATTENDANCE\n";
        }
        else if (percentage >= 75.0) {
            cout << "GOOD\n";
        }
        else if (percentage >= 50.0) {
            cout << "FAIR\n";
        }
        else {
            cout << "NEEDS IMPROVEMENT\n";
        }
    }
}


int old_main(){
    system("title Student Attendance System");
    system("color F0");//these are colour codes for the text and background

        system("cls");//system("cls") is for windows

    int choice;
    do {
        cout << "\n**** MAIN MENU ****\n";
        cout << "1. Add Student\n";
        cout << "2. Mark Attendance (30 Days)\n";
        cout << "3. Display Records\n";
        cout << "4. Display Attendance Percentage\n";
        cout << "5. Update Attendance\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudent(); break;
        case 2: markAttendance(); break;
        case 3: displayRecords(); break;
        case 4: displayStats(); break;
        case 5: updateAttendance(); break;
        case 6: cout << "Program Ended\n"; break;
        default: cout << "Invalid Choice\n";
        }
    } while (choice != 6);
    return 0;
}