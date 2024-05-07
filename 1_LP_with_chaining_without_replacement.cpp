// Consider the student database of N students and their marks. Make use of a hash table implementation to quickly insert and lookup students' Rollno and marks. Implement collision handling techniques-  linear probing with chaining without replacement. 
#include <iostream>
#include <vector>
using namespace std;

// Define the size of the hash table
const int table_size = 10;

// Define a struct to represent a Student, containing PNR (Personal Numeric Code) and marks
struct Student{
    int pnr;
    int marks;
};

// Define a class for the hash table
class Hashtable{
public:
    // Vector of pairs to represent the hash table, each element is a bucket that holds pairs of PNR and marks
    vector<pair<int, int>> table[table_size];

    // Hash function to calculate the index for a given PNR
    int hashfunction(int pnr){
        return pnr % table_size; // Simple modulus operation to map PNR to an index
    }

    // Function to insert a student's record into the hash table using linear probing
    void insertlp(int pnr, int marks){
        int index = hashfunction(pnr); // Calculate index using hash function
        while(!table[index].empty()){ // Loop until an empty slot is found
            index = (index + 1) % table_size; // Linear probing: move to the next slot
        }
        table[index].push_back({pnr, marks}); // Insert the record into the table
        cout<<"Student inserted successfully"<<endl;
    }

    // Function to delete a student's record from the hash table using linear probing
    void deletelp(int pnr){
        int index = hashfunction(pnr); // Calculate index using hash function
        while(!table[index].empty()){ // Loop until an empty slot is found
            for(auto it = table[index].begin(); it != table[index].end(); ++it){ // Iterate through elements in the bucket
                if(it->first == pnr){ // If PNR matches, delete the record
                    table[index].erase(it);
                    cout<<"Student with PNR "<<pnr<<" deleted successfully"<<endl;
                    return;
                }
            }
            index = (index + 1) % table_size; // Linear probing: move to the next slot
        }
        cout<<"Student with PNR "<<pnr<<" not found"<<endl; // PNR not found in the table
    }

    // Function to insert a student's record into the hash table using linear probing with chaining without replacement
    void insertlpchainwithoutrep(int pnr, int marks){
        int index = hashfunction(pnr); // Calculate index using hash function
        table[index].push_back({pnr, marks}); // Insert the record into the table
        cout<<"Student inserted successfully"<<endl;
    }

    // Function to search for a student's marks based on PNR
    int search(int pnr){
        int index = hashfunction(pnr); // Calculate index using hash function
        while(!table[index].empty()){ // Loop until an empty slot is found
            for(auto student : table[index]){ // Iterate through elements in the bucket
                if(student.first == pnr){ // If PNR matches, return marks
                    return student.second;
                }
            }
            index = (index + 1) % table_size; // Linear probing: move to the next slot
        }
        return -1; // PNR not found in the table
    }

    // Function to display the hash table
    void display(){
        for(int i = 0; i < table_size; i++){ // Iterate through each bucket in the table
            cout<< "Bucket "<<i<<" : ";
            for(auto it : table[i]){ // Iterate through elements in the bucket
                cout<<" ( "<<it.first<<" , "<<it.second<<" ) "; // Display PNR and marks
            }
            cout<<endl;
        }
    }
};

// Main function
int main(){
    Hashtable t; // Create an instance of Hashtable
    int choice;
    int pnr;
    int marks;
    do {
        // Display menu options
        cout<<"\nMenu : \n";
        cout<<"1 Insert using linear probing\n";
        cout<<"2 Insert using Linear Probing with Chaining without Replacement\n";
        cout<<"3 Search a student\n";
        cout<<"4 Delete a student\n";
        cout<<"5 Display table\n";
        cout<<"6 Exit\n";
        cout<<"Enter choice : ";
        cin>>choice; // Input choice from user
        switch(choice){ // Switch based on choice
            case 1:
                {cout<<"Enter PNR and marks : ";
                cin>>pnr>>marks;
                t.insertlp(pnr, marks); // Insert using linear probing
                break;}
            case 2:
                {cout<<"Enter PNR and marks : ";
                cin>>pnr>>marks;
                t.insertlpchainwithoutrep(pnr, marks); // Insert using linear probing with chaining without replacement
                break;}
            case 3:
                {cout<<"Enter PNR to search : ";
                cin>>pnr;
                int found = t.search(pnr); // Search for a student
                if(found == -1){
                    cout<<"No record found"<<endl;
                }
                else{
                    cout<<"Marks of student with PNR "<<pnr <<" is "<<found<<endl; // Display marks
                }
                break;}
            case 4:
                {cout<<"Enter PNR to delete : ";
                cin>>pnr;
                t.deletelp(pnr); // Delete a student
                break;}
            case 5:
                {cout<<"HASHTABLE : "<<endl;
                t.display(); // Display the hash table
                break;}
            case 6:
                {cout<<"Exiting..."<<endl;
                break;}
            default:
                cout<<"Enter a valid choice"<<endl; // Invalid choice
        }
    }while(choice != 6); // Continue until user chooses to exit
    return 0;
}

// Time Complexity: O(1) on average for insertion, deletion, and search operations.
