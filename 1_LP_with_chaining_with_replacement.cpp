// Consider the student database of N students and their marks. Make use of a hash table implementation to quickly insert and lookup students' PNR and marks. Implement collision handling techniques-  linear probing with chaining with replacement  
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

// Class representing a student with PNR and marks
class Student {
public:
    string pnr;
    int marks;

    Student(const string& pnr, int marks) : pnr(pnr), marks(marks) {}
};

// Hash Table class using linear probing with chaining and replacement
class HashTable {
private:
    static const int TABLE_SIZE = 10; // Size of the hash table
    vector<list<Student>> table; // Hash table using vector of linked lists

    // Hash function to map PNRs to table indices
    int hash(const string& pnr) const {
        int hashValue = 0;
        for (char c : pnr) {
            hashValue = (hashValue * 31 + c) % TABLE_SIZE;
        }
        return hashValue;
    }

public:
    HashTable() : table(TABLE_SIZE) {}

    // Insert a student into the hash table
    void insert(const string& pnr, int marks) {
        int index = hash(pnr);
        list<Student>& chain = table[index];

        // Check if PNR already exists in the hash table
        auto it = find_if(chain.begin(), chain.end(), [&](const Student& student) {
            return student.pnr == pnr;
        });

        if (it != chain.end()) {
            // Student already exists, update marks
            it->marks = marks;
        } else {
            // Insert new student into the chain
            chain.push_back(Student(pnr, marks));
        }
    }

    // Lookup a student's marks by PNR
    int lookup(const string& pnr) {
        int index = hash(pnr);
        list<Student>& chain = table[index];

        // Search for student in the chain
        auto it = find_if(chain.begin(), chain.end(), [&](const Student& student) {
            return student.pnr == pnr;
        });

        if (it != chain.end()) {
            return it->marks;
        } else {
            // Student not found
            return -1;
        }
    }

    // Print the hash table
    void printTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "Bucket " << i << ": ";
            for (const auto& student : table[i]) {
                cout << "(" << student.pnr << ", " << student.marks << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable hashTable;

    // Insert students into the hash table
    hashTable.insert("A123", 85);
    hashTable.insert("B456", 92);
    hashTable.insert("C789", 78);
    hashTable.insert("D012", 88);
    hashTable.insert("E345", 95);
    hashTable.insert("F678", 82);
    hashTable.insert("G901", 90);

    // Lookup student marks by PNR
    string pnrToLookup = "E345";
    int marks = hashTable.lookup(pnrToLookup);
    if (marks != -1) {
        cout << "Marks of student with PNR " << pnrToLookup << ": " << marks << endl;
    } else {
        cout << "Student with PNR " << pnrToLookup << " not found." << endl;
    }

    // Print the hash table
    cout << "Hash Table:" << endl;
    hashTable.printTable();

    return 0;
}
