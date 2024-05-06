// Department maintains student information. the file contains rollno, name, division, and address. Allow user to add, edit, delete, insert and search information of student. use sequential file to maintain the data
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Structure to represent student information
struct Student {
    int rollNo;
    string name;
    string division;
    string address;
};

// Function to display a student record
void displayStudent(const Student& student) {
    cout << "Roll No: " << student.rollNo << endl;
    cout << "Name: " << student.name << endl;
    cout << "Division: " << student.division << endl;
    cout << "Address: " << student.address << endl;
}

// Function to add a new student record to the file
void addStudent(const Student& student) {
    ofstream outFile("students.dat", ios::binary | ios::app);
    if (!outFile) {
        cerr << "Error: Unable to open file!" << endl;
        return;
    }
    outFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));
    outFile.close();
    cout << "Student record added successfully!" << endl;
}

// Function to display all student records stored in the file
void displayAllStudents() {
    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cerr << "Error: Unable to open file!" << endl;
        return;
    }
    Student student;
    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        displayStudent(student);
        cout << "---------------------------" << endl;
    }
    inFile.close();
}

// Main function to interact with the user
int main() {
    int choice;
    Student student;

    while (true) {
        cout << "\nStudent Information Management System" << endl;
        cout << "1. Add Student Record" << endl;
        cout << "2. Display All Students" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Roll No: ";
                cin >> student.rollNo;
                cin.ignore(); // Clear newline character from input buffer
                cout << "Enter Name: ";
                getline(cin, student.name);
                cout << "Enter Division: ";
                getline(cin, student.division);
                cout << "Enter Address: ";
                getline(cin, student.address);
                addStudent(student);
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                cout << "Exiting program..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }

    return 0;
}
