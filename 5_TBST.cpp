// Write a program to convert given binary search tree into inorder threaded binary search tree and its inorder traversal
#include <iostream>
using namespace std;

// Definition of a node in the Binary Search Tree
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

// Binary Search Tree class
class BinarySearchTree {
private:
    Node* root;

    // Helper function to insert a node into the BST
    Node* insertRecursive(Node* root, int value) {
        if (root == nullptr) {
            return new Node(value);
        }

        if (value < root->data) {
            root->left = insertRecursive(root->left, value);
        } else if (value > root->data) {
            root->right = insertRecursive(root->right, value);
        }

        return root;
    }

    // Helper function to perform inorder traversal and thread the tree
    void threadInorder(Node* root, Node*& prev) {
        if (root == nullptr) {
            return;
        }

        // Recursively thread the left subtree
        threadInorder(root->left, prev);

        // Thread the current node
        if (prev != nullptr && prev->right == nullptr) {
            prev->right = root;
            prev->rightThread = true;
        }
        prev = root;

        // Recursively thread the right subtree
        threadInorder(root->right, prev);
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    // Function to insert a new node into the BST
    void insert(int value) {
        root = insertRecursive(root, value);
    }

    // Function to convert BST to inorder threaded BST
    void convertToThreaded() {
        Node* prev = nullptr;
        threadInorder(root, prev);
    }

    // Function to perform inorder traversal of the threaded BST
    void threadedInorderTraversal() {
        cout << "Inorder traversal (threaded): ";
        Node* curr = root;

        // Find the leftmost node in the tree
        while (curr != nullptr && curr->left != nullptr) {
            curr = curr->left;
        }

        // Traverse the threaded tree using threads
        while (curr != nullptr) {
            cout << curr->data << " ";

            if (curr->rightThread) {
                curr = curr->right;
            } else {
                curr = curr->right;
                while (curr != nullptr && curr->left != nullptr) {
                    curr = curr->left;
                }
            }
        }

        cout << endl;
    }
};

int main() {
    BinarySearchTree bst;

    // Insert nodes into the BST
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    // Convert BST to threaded BST
    bst.convertToThreaded();

    // Perform inorder traversal of the threaded BST
    bst.threadedInorderTraversal();

    return 0;
}

// T.C.
// Insertion: O(h) where h is the height of the BST
// Conversion to threaded BST: O(n) where n is the number of nodes in the BST
// Threaded Inorder Traversal: O(n) where n is the number of nodes in the BST
// S.C.
// O(n) where n is the number of nodes in the BST
// Note: The space complexity is O(n) due to the recursive nature of the threadedInorderTraversal function.
// The space complexity of the threadedInorderTraversal function is O(n) due to the recursive nature of the function.