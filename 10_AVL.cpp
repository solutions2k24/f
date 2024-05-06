// Write a C++ program to construct AVL Tree. Implement following operations. 
// a.Insert b. level order traversal c. Print height of tree

#include <iostream>
#include <queue>
#include <cmath>  // For max function

using namespace std;

// Definition of a node in the AVL Tree
class AVLNode {
public:
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        height = 1;  // Initial height of a new node is 1
    }
};

class AVLTree {
private:
    AVLNode* root;

    // Get height of a node (return 0 for nullptr)
    int getHeight(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // Calculate balance factor of a node
    int getBalanceFactor(AVLNode* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Update height of a node
    void updateHeight(AVLNode* node) {
        if (node == nullptr)
            return;
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    // Perform right rotation on a node
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Perform left rotation on a node
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Recursive function to insert a value into the AVL Tree
    AVLNode* insertRecursive(AVLNode* node, int value) {
        // Perform standard BST insertion
        if (node == nullptr)
            return new AVLNode(value);

        if (value < node->data)
            node->left = insertRecursive(node->left, value);
        else if (value > node->data)
            node->right = insertRecursive(node->right, value);
        else  // Duplicate keys are not allowed in AVL Tree
            return node;

        // Update height of the current node
        updateHeight(node);

        // Get the balance factor to check if this node became unbalanced
        int balance = getBalanceFactor(node);

        // Left Left Case (LL)
        if (balance > 1 && value < node->left->data)
            return rightRotate(node);

        // Right Right Case (RR)
        if (balance < -1 && value > node->right->data)
            return leftRotate(node);

        // Left Right Case (LR)
        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case (RL)
        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Level order traversal (Breadth-First Search)
    void levelOrderTraversal(AVLNode* node) {
        if (node == nullptr)
            return;

        queue<AVLNode*> q;
        q.push(node);

        while (!q.empty()) {
            AVLNode* current = q.front();
            q.pop();

            cout << current->data << " ";

            if (current->left != nullptr)
                q.push(current->left);

            if (current->right != nullptr)
                q.push(current->right);
        }
    }

public:
    AVLTree() {
        root = nullptr;
    }

    // Public method to insert a value into the AVL Tree
    void insert(int value) {
        root = insertRecursive(root, value);
    }

    // Public method to perform level order traversal of the AVL Tree
    void levelOrder() {
        cout << "Level Order Traversal: ";
        levelOrderTraversal(root);
        cout << endl;
    }

    // Public method to get the height of the AVL Tree
    int getHeight() {
        return getHeight(root);
    }
};

int main() {
    AVLTree avl;

    // Insert elements into the AVL Tree
    avl.insert(50);
    avl.insert(30);
    avl.insert(70);
    avl.insert(20);
    avl.insert(40);
    avl.insert(60);
    avl.insert(80);

    // Perform level order traversal of the AVL Tree
    avl.levelOrder();

    // Print height of the AVL Tree
    cout << "Height of the AVL Tree: " << avl.getHeight() << endl;

    return 0;
}

// Time Complexity:
// Insertion: O(log n)
// Level Order Traversal: O(n)
// Get Height: O(1)