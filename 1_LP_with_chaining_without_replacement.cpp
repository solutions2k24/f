// Consider the student database of N students and their marks. Make use of a hash table implementation to quickly insert and lookup students' Rollno and marks. Implement collision handling techniques-  linear probing with chaining without replacement. 
#include <iostream>
using namespace std;

struct rec {
    int key;
    int chain;
};

class Hashing {
public:
    rec hashtable[10];

    Hashing() {
        for (int i = 0; i < 10; i++) {
            hashtable[i].key = -1;
            hashtable[i].chain = -1;
        }
    }

    void insert(int r);
    bool searching(int r);
    void display();
};

void Hashing::insert(int r) {
    int ind = r % 10;

    if (hashtable[ind].key == -1) {
        hashtable[ind].key = r;
    } else {
        int nxt = (ind + 1) % 10;
        while (hashtable[nxt].key != -1) {
            nxt = (nxt + 1) % 10;
        }
        hashtable[nxt].key = r;

        // Update chaining
        int tmp = ind;
        while (hashtable[tmp].chain != -1) {
            tmp = hashtable[tmp].chain;
        }
        hashtable[tmp].chain = nxt;
    }
}

bool Hashing::searching(int r) {
    int ind = r % 10;

    while (ind != -1) {
        if (hashtable[ind].key == r) {
            return true; // Found in the initial slot
        }
        ind = hashtable[ind].chain;
    }

    return false; // Not found in the chain
}

void Hashing::display() {
    for (int i = 0; i < 10; i++) {
        cout << "Index: " << i << " Roll No: " << hashtable[i].key << " Chain: " << hashtable[i].chain << endl;
    }
}

int main() {
    Hashing hs;
    int choice;
    int roll;

    while (true) {
        cout << "1. Insert" << endl;
        cout << "2. Search" << endl;
        cout << "3. Display" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the number of elements to be inserted: ";
                int n;
                cin >> n;
                cout << "Enter the roll numbers: " << endl;
                while (n--) {
                    cin >> roll;
                    hs.insert(roll);
                }
                break;
            case 2:
                cout << "Enter the roll number to be searched: ";
                cin >> roll;
                if (hs.searching(roll)) {
                    cout << "Roll number " << roll << " found" << endl;
                } else {
                    cout << "Roll number " << roll << " not found" << endl;
                }
                break;
            case 3:
                hs.display();
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice" << endl;
        }
    }

    return 0;
}


//     cout<<hs.searching(12)<<endl;    //element not present at correct hash index 
//     cout<<hs.searching(33)<<endl;    //element present in chain at correct hash index
//     cout<<hs.searching(32)<<endl;    //element not in chain
//     cout<<hs.searching(16)<<endl;    //element at correct hash index

// Time Complexity: O(1) for insertion and searching
