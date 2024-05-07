// Write a C++ program to inorder threaded binary search tree with n nodes and implement following operations
// 1.Insert a new node
// 2. Inorder traversal

#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    bool leftThread;
    bool rightThread;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        leftThread = true;
        rightThread = true;
    }
};

class ThreadedBST {
private:
    Node* root;

    // Helper function to perform threaded inorder traversal
    void threadedInorder(Node* root) {
        Node* curr = leftmost(root);

        // Traverse using threads
        while (curr != nullptr) {
            cout << curr->data << " ";
            if (curr->rightThread) {
                curr = curr->right;
            } else {
                curr = leftmost(curr->right);
            }
        }
    }

    // Helper function to find the leftmost node
    Node* leftmost(Node* node) {
        if (node == nullptr)
            return nullptr;
        while (node->left != nullptr && !node->leftThread)
            node = node->left;
        return node;
    }

    Node* insertNode(Node* root, int val) {
        Node* newNode = new Node(val);
        if (root == nullptr) {
            return newNode;  // Return newNode as the new root
        }

        Node* curr = root;
        Node* parent = nullptr;

        // Find the position to insert the new node
        while (curr != nullptr) {
            parent = curr;
            if (val < curr->data) {
                if (curr->leftThread) {
                    // Insert new node as left child
                    newNode->left = curr->left;
                    newNode->right = curr;
                    curr->left = newNode;
                    curr->leftThread = false;  // Update thread flag
                    return root;  // Return the original root
                }
                curr = curr->left;
            }
            else {
                if (curr->rightThread) {
                    // Insert new node as right child
                    newNode->left = curr;
                    newNode->right = curr->right;
                    curr->right = newNode;
                    curr->rightThread = false;  // Update thread flag
                    return root;  // Return the original root
                }
            curr = curr->right;
        }
    }

    return root;  // Return the original root if no insertion was performed
}


public:
    ThreadedBST() {
        root = nullptr;
    }

    // Public function to insert a new value into the threaded BST
    void insert(int value) {
        root = insertNode(root, value);
    }

    // Public function to perform threaded inorder traversal
    void inorder() {
        threadedInorder(root);
        cout << endl;
    }
};

int main() {
    ThreadedBST t;

    // Insert elements into the threaded BST
    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(3);
    t.insert(7);
    t.insert(12);
    t.insert(18);

    // Perform threaded inorder traversal
    t.inorder(); // Output: 3 5 7 10 12 15 18
    return 0;
}

// Time Complexity: O(n) for inserting n nodes into the threaded binary search tree
