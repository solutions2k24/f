// Write a C++ program to inorder threaded binary search tree with n nodes and implement following operations
// 1.Insert a new node
// 2. Inorder traversal

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    bool rightThread;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        rightThread = false;
    }
};

class ThreadedBST {
private:
    Node* root;

    Node* insertRecursive(Node* root, int value) {
        if (root == nullptr) {
            return new Node(value);
        }

        if (value < root->data) {
            root->left = insertRecursive(root->left, value);
        } else if (value > root->data) {
            if (root->rightThread) {
                root->rightThread = false;
                Node* newNode = new Node(value);
                newNode->right = root->right;
                root->right = newNode;
            } else {
                root->right = insertRecursive(root->right, value);
            }
        }

        return root;
    }

    void inorderRecursive(Node* root) {
        if (root == nullptr) {
            return;
        }

        inorderRecursive(root->left);
        cout << root->data << " ";
        inorderRecursive(root->right);
    }

public:
    ThreadedBST() {
        root = nullptr;
    }

    void insert(int value) {
        root = insertRecursive(root, value);
    }

    void inorder() {
        inorderRecursive(root);
        cout << endl;
    }
};

int main() {
    ThreadedBST t;
    
    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(3);
    t.insert(7);
    t.insert(12);
    t.insert(18);

    t.inorder(); // 3 5 7 10 12 15 18
    return 0;
}

// Time Complexity: O(n)