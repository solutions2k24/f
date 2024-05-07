#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// Definition of a node in the Binary Search Tree
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Binary Search Tree class
class BinarySearchTree {
private:
    Node* root;

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

    void inorderRecursive(Node* root) {
        if (root == nullptr) {
            return;
        }

        inorderRecursive(root->left);
        cout << root->data << " ";
        inorderRecursive(root->right);
    }

    void preorderRecursive(Node* root) {
        if (root == nullptr) {
            return;
        }

        cout << root->data << " ";
        preorderRecursive(root->left);
        preorderRecursive(root->right);
    }

    void postorderRecursive(Node* root) {
        if (root == nullptr) {
            return;
        }

        postorderRecursive(root->left);
        postorderRecursive(root->right);
        cout << root->data << " ";
    }

    int getHeightRecursive(Node* root) {
        if (root == nullptr) {
            return 0;
        }

        int leftHeight = getHeightRecursive(root->left);
        int rightHeight = getHeightRecursive(root->right);

        return 1 + max(leftHeight, rightHeight);
    }

    Node* mirrorTreeRecursive(Node* root) {
        if (root == nullptr) {
            return nullptr;
        }

        Node* mirroredLeft = mirrorTreeRecursive(root->right);
        Node* mirroredRight = mirrorTreeRecursive(root->left);

        root->left = mirroredLeft;
        root->right = mirroredRight;

        return root;
    }

     Node* buildTreeFromInorderAndPreorder(vector<int>& inorder, vector<int>& preorder, int inStart, int inEnd, int& preIndex) {
        if (inStart > inEnd) {
            return nullptr;
        }

        int rootValue = preorder[preIndex++];
        Node* rootNode = new Node(rootValue);

        if (inStart == inEnd) {
            return rootNode;
        }

        int rootIndexInInorder;
        for (int i = inStart; i <= inEnd; ++i) {
            if (inorder[i] == rootValue) {
                rootIndexInInorder = i;
                break;
            }
        }

        rootNode->left = buildTreeFromInorderAndPreorder(inorder, preorder, inStart, rootIndexInInorder - 1, preIndex);
        rootNode->right = buildTreeFromInorderAndPreorder(inorder, preorder, rootIndexInInorder + 1, inEnd, preIndex);

        return rootNode;
    }

    Node* deleteNodeRecursive(Node* root, int value) {
        if (root == nullptr) {
            return nullptr;
        }

        if (value < root->data) {
            root->left = deleteNodeRecursive(root->left, value);
        } else if (value > root->data) {
            root->right = deleteNodeRecursive(root->right, value);
        } else {
            // Node to be deleted found
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            } else {
                // Node has two children
                Node* successor = findMin(root->right);
                root->data = successor->data;
                root->right = deleteNodeRecursive(root->right, successor->data);
            }
        }

        return root;
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* cloneTree(Node* original) {
        if (original == nullptr) {
            return nullptr;
        }

        Node* newNode = new Node(original->data);
        newNode->left = cloneTree(original->left);
        newNode->right = cloneTree(original->right);
        return newNode;
    }

    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }

        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    // Copy constructor
    BinarySearchTree(const BinarySearchTree& other) {
        root = cloneTree(other.root);
    }

    // Copy assignment operator
    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this != &other) {
            // Clear existing tree
            clear(root);

            // Clone the other tree
            root = cloneTree(other.root);
        }
        return *this;
    }

    void insert(int value) {
        root = insertRecursive(root, value);
    }

    void inorder() {
        cout << "Inorder traversal (recursive): ";
        inorderRecursive(root);
        cout << endl;
    }

    void preorder() {
        cout << "Preorder traversal (recursive): ";
        preorderRecursive(root);
        cout << endl;
    }

    void postorder() {
        cout << "Postorder traversal (recursive): ";
        postorderRecursive(root);
        cout << endl;
    }

    void inorderNonRecursive() {
        cout << "Inorder traversal (non-recursive): ";
        stack<Node*> s;
        Node* curr = root;

        while (curr != nullptr || !s.empty()) {
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            s.pop();
            cout << curr->data << " ";

            curr = curr->right;
        }
        cout << endl;
    }

    void preorderNonRecursive() {
        cout << "Preorder traversal (non-recursive): ";
        stack<Node*> s;
        s.push(root);

        while (!s.empty()) {
            Node* curr = s.top();
            s.pop();

            if (curr != nullptr) {
                cout << curr->data << " ";
                s.push(curr->right);
                s.push(curr->left);
            }
        }

        cout << endl;
    }

    void postorderNonRecursive() {
        cout << "Postorder traversal (non-recursive): ";
        stack<Node*> s;
        s.push(root);
        stack<int> out;

        while (!s.empty()) {
            Node* curr = s.top();
            s.pop();

            if (curr != nullptr) {
                out.push(curr->data);
                s.push(curr->left);
                s.push(curr->right);
            }
        }

        while (!out.empty()) {
            cout << out.top() << " ";
            out.pop();
        }

        cout << endl;
    }

    int getHeight() {
        return getHeightRecursive(root);
    }

    void mirrorTree() {
        root = mirrorTreeRecursive(root);
    }

    Node* buildTreeFromInorderAndPreorder(vector<int>& inorder, vector<int>& preorder) {
        int preIndex = 0;
        return buildTreeFromInorderAndPreorder(inorder, preorder, 0, inorder.size() - 1, preIndex);
    }

    void deleteNode(int value) {
        root = deleteNodeRecursive(root, value);
    }

    ~BinarySearchTree() {
        // Clean up memory by deleting all nodes in the tree
        deleteTree(root);
    }   

private:
    void deleteTree(Node* root) {
        if (root == nullptr) {
            return;
        }

        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
};

int main() {
    BinarySearchTree bst;

    // 1. Insert nodes into the Binary Search Tree
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    // 2. Perform recursive traversals
    bst.inorder();
    bst.preorder();
    bst.postorder();

    // 2. Perform non-recursive traversals
    bst.inorderNonRecursive();
    bst.preorderNonRecursive();
    bst.postorderNonRecursive();

    // 3. Find the height of the tree
    cout << "Height of the tree: " << bst.getHeight() << endl;

    // 4. Create mirror image of the tree
    bst.mirrorTree();

    // 4. Perform inorder traversal on mirrored tree
    cout << "Inorder traversal of mirrored tree ";
    bst.inorder();
    
    // 5. Delete a node (e.g., delete node with value 30)
    bst.deleteNode(30);

    // 5. Perform inorder traversal after deleting node
    cout << "Inorder traversal after deleting node with value 30: ";
    bst.inorder();

    // 6. Build a tree from inorder and preorder traversals
    vector<int> inorder = {20, 30, 40, 50, 60, 70, 80};
    vector<int> preorder = {50, 30, 20, 40, 70, 60, 80};
    Node* constructedRoot = bst.buildTreeFromInorderAndPreorder(inorder, preorder);
    cout << "Inorder traversal of constructed tree: ";
    bst.inorder();

    // 7. Create a clone of the original tree
    BinarySearchTree clonedTree;
    clonedTree = bst;  // This uses the default assignment operator for deep copy

    // 7. Erase all nodes in the original tree
    bst.~BinarySearchTree();  // This will delete all nodes in the original tree

    // 7. Perform operations on clonedTree, print inorder traversal of clonedTree
    cout << "Inorder traversal of cloned tree: ";
    clonedTree.inorder();
    return 0;
}

// Time complexity of the operations:
// Insertion: O(h), where h is the height of the tree
// Recursive traversals: O(n), where n is the number of nodes in the tree
// Non-recursive traversals: O(n), where n is the number of nodes in the tree
// Height calculation: O(n), where n is the number of nodes in the tree
// Mirror tree creation: O(n), where n is the number of nodes in the tree
// Build tree from inorder and preorder: O(n^2), where n is the number of nodes in the tree
// Node deletion: O(h), where h is the height of the tree
// Tree deletion: O(n), where n is the number of nodes in the tree
// Cloning: O(n), where n is the number of nodes in the tree
