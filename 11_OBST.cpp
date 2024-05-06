// Given sequence k = k1<; k2<..... kn of n sorted keys, with a search probability pi for each
// key ki . Build the Binary search tree that has the least search cost given the access probability
// for each key. Display weight matrix, cost matrix and root matrix.
// test your program for following example:
// k1=do, k2=if, k3=read, k4= while
// p1 = 1, p2 = 3, p3 = 1, p4 = 3 
// q0 = 1, q1 = 2, q2 = 1, q3= 1, q4 = 3

#include <iostream>
#include <climits>
#include <cstring>
using namespace std;

// Define maximum array sizes
const int MAX_KEYS = 5;

// Structure to represent a node in the BST
struct BSTNode {
    string key;
    int prob;  // Search probability
};

// Function to build the optimal BST
void buildOptimalBST(string keys[], int p[], int q[]) {
    int n = MAX_KEYS;  // Number of keys

    // Define matrices for weights, costs, and roots
    int weight[MAX_KEYS + 1][MAX_KEYS + 1];
    int cost[MAX_KEYS + 1][MAX_KEYS + 1];
    int root[MAX_KEYS + 1][MAX_KEYS + 1];

    // Initialize matrices
    memset(weight, 0, sizeof(weight));
    memset(cost, 0, sizeof(cost));
    memset(root, 0, sizeof(root));

    // Initialize the diagonal values (single keys)
    for (int i = 1; i <= n; i++) {
        weight[i][i] = q[i - 1];
        cost[i][i] = q[i - 1];
        root[i][i] = i;
    }

    // Fill the matrices using bottom-up approach
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            cost[i][j] = INT_MAX;

            // Calculate weight sum from qi to qj
            weight[i][j] = weight[i][j - 1] + p[j - 1] + q[j];

            // Try all keys as the root
            for (int r = i; r <= j; r++) {
                int tempCost = cost[i][r - 1] + cost[r + 1][j] + weight[i][j];
                if (tempCost < cost[i][j]) {
                    cost[i][j] = tempCost;
                    root[i][j] = r;
                }
            }
        }
    }

    // Display weight matrix
    cout << "Weight Matrix:" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << weight[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    // Display cost matrix
    cout << "Cost Matrix:" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << cost[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    // Display root matrix
    cout << "Root Matrix:" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << root[i][j] << "\t";
        }
        cout << endl;
    }
}

int main() {
    string keys[MAX_KEYS] = {"do", "if", "read", "while"};
    int p[MAX_KEYS] = {1, 3, 1, 3};
    int q[MAX_KEYS + 1] = {1, 2, 1, 1, 3};  // Include q0 as well

    // Build the optimal BST and display matrices
    buildOptimalBST(keys, p, q);

    return 0;
}

// Time Complexity:
// O(n^3)