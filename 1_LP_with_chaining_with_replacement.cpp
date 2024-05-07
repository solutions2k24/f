// Consider the student database of N students and their marks. Make use of a hash table implementation to quickly insert and lookup students' PNR and marks. Implement collision handling techniques-  linear probing with chaining with replacement  
#include <iostream>
#include <vector>
using namespace std;

const int table_size = 10;

struct Student{
    int pnr;
    int marks;
};

class Hashtable{
public:
    vector<pair<int, int>> table[table_size];

    int hashfunction(int pnr){
        return pnr % table_size;
    }

    void insertlp(int pnr, int marks){
        int index = hashfunction(pnr);
        while(!table[index].empty()){
            index = (index + 1) % table_size;
        }
        table[index].push_back({pnr, marks});
        cout<<"Student inserted successfully"<<endl;
    }

    void deletelp(int pnr){
        int index = hashfunction(pnr);
        while(!table[index].empty()){
            for(auto it = table[index].begin(); it != table[index].end(); ++it){
                if(it->first == pnr){
                    table[index].erase(it);
                    cout<<"Student with PNR "<<pnr<<" deleted successfully"<<endl;
                    return;
                }
            }
            index = (index + 1) % table_size;
        }
        cout<<"Student with PNR "<<pnr<<" not found"<<endl;
    }

    void insertlpchainwithrep(int pnr, int marks){
        int index = hashfunction(pnr);
        if(!table[index].empty()){
            int temppnr = table[index][0].first;
            int tempmarks = table[index][0].second;
            if(hashfunction(temppnr)==index){
                table[index].push_back({pnr, marks});
            }
            else{
                table[index][0].first = pnr;
                table[index][0].second = marks;
                while (!table[index].empty())
                {
                    index = (index+1) % table_size;
                }
                table[index].push_back({temppnr, tempmarks});
            }
        }
        else
        {
            table[index].push_back({pnr, marks});
        }
        cout<<"student inserted successfully"<<endl;
    }

    int search(int pnr){
        int index = hashfunction(pnr);
        while(!table[index].empty()){
            for(auto student : table[index]){
                if(student.first == pnr){
                    return student.second;
                }
            }
            index = (index + 1) % table_size;
        }
        return -1;
    }

    void display(){
        for(int i = 0; i < table_size; i++){
            cout<< "Bucket "<<i<<" : ";
            for(auto it : table[i]){
                cout<<" ( "<<it.first<<" , "<<it.second<<" ) ";
            }
            cout<<endl;
        }
    }
};

int main(){
    Hashtable t;
    int choice;
    int pnr;
    int marks;
    do {
        cout<<"\nMenu : \n";
        cout<<"1 Insert using linear probing\n";
        cout<<"2 Insert using Linear Probing with Chaining with Replacement\n";
        cout<<"3 Search a student\n";
        cout<<"4 Delete a student\n";
        cout<<"5 Display table\n";
        cout<<"6 Exit\n";
        cout<<"Enter choice : ";
        cin>>choice;
        switch(choice){
            case 1:
                {cout<<"Enter PNR and marks : ";
                cin>>pnr>>marks;
                t.insertlp(pnr, marks);
                break;}
            case 2:
                {cout<<"Enter PNR and marks : ";
                cin>>pnr>>marks;
                t.insertlpchainwithrep(pnr, marks);
                break;}
            case 3:
                {cout<<"Enter PNR to search : ";
                cin>>pnr;
                int found = t.search(pnr);
                if(found == -1){
                    cout<<"No record found"<<endl;
                }
                else{
                    cout<<"Marks of student with PNR "<<pnr <<" is "<<found<<endl;
                }
                break;}
            case 4:
                {cout<<"Enter PNR to delete : ";
                cin>>pnr;
                t.deletelp(pnr);
                break;}
            case 5:
                {cout<<"HASHTABLE : "<<endl;
                t.display();
                break;}
            case 6:
                {cout<<"Exiting..."<<endl;
                break;}
            default:
                cout<<"Enter a valid choice"<<endl;
        }
    }while(choice != 6);
    return 0;
}

// Time Complexity : O(N) for searching, O(1) for insertion and deletion
