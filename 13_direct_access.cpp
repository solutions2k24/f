// 2. Department maintains student information. the file contains rollno, name, division, and address. Allow user to add, edit, delete, insert and search information of student. use direct access file to maintain the data
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// Structure representing a student record
struct Student {
    int rollno;
    char name[50];
    char division[10];
    char address[100];
};

// Function to add a new student record to the file
void addStudent(fstream& file) {
    Student student;
    cout << "Enter Roll No: ";
    cin >> student.rollno;
    cin.ignore(); // Ignore the newline character in the input buffer
    cout << "Enter Name: ";
    cin.getline(student.name, sizeof(student.name));
    cout << "Enter Division: ";
    cin.getline(student.division, sizeof(student.division));
    cout << "Enter Address: ";
    cin.getline(student.address, sizeof(student.address));

    // Write the student record to the file at the specified position
    file.seekp(student.rollno * sizeof(Student));
    file.write(reinterpret_cast<char*>(&student), sizeof(Student));

    cout << "Student record added successfully.\n";
}

// Function to search for a student record by roll number
void searchStudent(fstream& file) {
    int rollno;
    cout << "Enter Roll No to search: ";
    cin >> rollno;

    // Read the student record from the file at the specified position
    file.seekg(rollno * sizeof(Student));
    Student student;
    file.read(reinterpret_cast<char*>(&student), sizeof(Student));

    if (file.eof()) {
        cout << "Student with Roll No " << rollno << " not found." << endl;
    } else {
        cout << "Student Record:" << endl;
        cout << "Roll No: " << student.rollno << endl;
        cout << "Name: " << student.name << endl;
        cout << "Division: " << student.division << endl;
        cout << "Address: " << student.address << endl;
    }
}

// Function to edit an existing student record
void editStudent(fstream& file) {
    int rollno;
    cout << "Enter Roll No to edit: ";
    cin >> rollno;

    // Read the student record from the file at the specified position
    file.seekg(rollno * sizeof(Student));
    Student student;
    file.read(reinterpret_cast<char*>(&student), sizeof(Student));

    if (file.eof()) {
        cout << "Student with Roll No " << rollno << " not found." << endl;
        return;
    }

    cout << "Editing Student Record:" << endl;
    cout << "Current Name: " << student.name << endl;
    cout << "Current Division: " << student.division << endl;
    cout << "Current Address: " << student.address << endl;

    cin.ignore(); // Ignore the newline character in the input buffer
    cout << "Enter New Name: ";
    cin.getline(student.name, sizeof(student.name));
    cout << "Enter New Division: ";
    cin.getline(student.division, sizeof(student.division));
    cout << "Enter New Address: ";
    cin.getline(student.address, sizeof(student.address));

    // Write the updated student record back to the file
    file.seekp(rollno * sizeof(Student));
    file.write(reinterpret_cast<char*>(&student), sizeof(Student));

    cout << "Student record updated successfully.\n";
}

// Function to delete a student record
void deleteStudent(fstream& file) {
    int rollno;
    cout << "Enter Roll No to delete: ";
    cin >> rollno;

    // "Delete" the student record by marking it as empty or invalid
    Student student;
    student.rollno = -1; // Mark as invalid

    file.seekp(rollno * sizeof(Student));
    file.write(reinterpret_cast<char*>(&student), sizeof(Student));

    cout << "Student record deleted successfully.\n";
}

int main() {
    fstream file("students.dat", ios::binary | ios::in | ios::out);

    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return 1;
    }

    while (true) {
        cout << "\n1. Add Student\n";
        cout << "2. Search Student\n";
        cout << "3. Edit Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(file);
                break;
            case 2:
                searchStudent(file);
                break;
            case 3:
                editStudent(file);
                break;
            case 4:
                deleteStudent(file);
                break;
            case 5:
                cout << "Exiting program.\n";
                file.close();
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

// Time Complexity: O(1) for each operation
// Space Complexity: O(N) where N is the number of student records stored in the file
