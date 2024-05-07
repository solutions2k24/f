//Write a c++ program to print topological order of given Directed acyclic Graph
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adj;

    void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& stack) {
        visited[v] = true;

        for (int i : adj[v]) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, stack);
            }
        }

        stack.push(v);
    }

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void topologicalSort() {
        stack<int> stack;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, stack);
            }
        }

        cout << "Topological order: ";
        while (!stack.empty()) {
            cout << stack.top() << " ";
            stack.pop();
        }
        cout << endl;
    }
};

int main() {
    int V, E; // Number of vertices and edges
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    Graph g(V);

    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << "Topological Order:" << endl;
    g.topologicalSort();

    return 0;
}


// Input
// 6 6
// 5 2
// 5 0
// 4 0
// 4 1
// 2 3
// 3 1

// Output
// Topological order: 5 4 2 3 1 0

// Time Complexity: O(V+E)
