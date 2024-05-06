// Input a list of more than 20 correctly spelled lowercase words. The words are inserted into the hash table. Handle collision using separate chaining. After the reading of the dictionary file is complete, the program prompts the user for input. After input is obtained, each word that the user enters into the program is looked up within the hash table to see if it exists. If the user entered word exists within the hash table, then that word is spelled correctly.
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Node {
public:
    string word;
    Node* next;

    Node() {
        word = "";
        next = nullptr;
    }

    Node(string s) {
        word = s;
        next = nullptr;
    }
};

class Hashing {
public:
    static const int tableSize = 10;
    Node* table[tableSize];

    Hashing() {
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    int HashFn(const string& word) {
        int hash = 0;
        for (char ch : word) {
            hash += int(ch);
        }
        return hash % tableSize;
    }

    void insertWord(const string& word) {
        int index = HashFn(word);
        if (table[index] == nullptr) {
            table[index] = new Node(word);
        } else {
            Node* newNode = new Node(word);
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

    bool searchWord(const string& word) {
        int index = HashFn(word);
        Node* temp = table[index];

        while (temp != nullptr) {
            if (temp->word == word) {
                return true; // Word found
            }
            temp = temp->next;
        }
        return false; // Word not found
    }

    void Display() {
        for (int i = 0; i < tableSize; i++) {
            cout << "[" << i << "]: ";

            Node* temp = table[i];

            while (temp != nullptr) {
                cout << temp->word << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
};

int main() {
    Hashing hashTable;

    ifstream infile("dictionary.txt"); // Assuming dictionary file contains words
    if (!infile) {
        cerr << "Error: Unable to open dictionary file." << endl;
        return 1;
    }

    string word;
    while (infile >> word) {
        hashTable.insertWord(word);
    }

    infile.close();

    cout << "Hash Table Contents:" << endl;
    hashTable.Display();

    string userInput;
    cout << "\nEnter a word to check its spelling: ";
    cin >> userInput;

    if (hashTable.searchWord(userInput)) {
        cout << userInput << " is spelled correctly." << endl;
    } else {
        cout << userInput << " is spelled incorrectly or not found in the dictionary." << endl;
    }
    return 0;
}

// Time Complexity: O(n) where n is the number of words in the dictionary file
