// Given a directed acyclic graph, a. write a program for topological ordering of vertices b. DFS traversal 

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adjMatrix; // Adjacency matrix

public:
    Graph(int vertices) : V(vertices), adjMatrix(vertices, vector<int>(vertices, 0)) {}

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1; // Mark edge from u to v
    }

    void topologicalSort() {
        vector<int> inDegree(V, 0); // Array to store in-degrees of vertices
        stack<int> stk;

        // Calculate in-degrees of each vertex
        for (int u = 0; u < V; ++u) {
            for (int v = 0; v < V; ++v) {
                if (adjMatrix[u][v] == 1) {
                    ++inDegree[v];
                }
            }
        }

        // Push vertices with in-degree 0 into the stack
        for (int u = 0; u < V; ++u) {
            if (inDegree[u] == 0) {
                stk.push(u);
            }
        }

        // Perform topological sorting using Kahn's algorithm
        cout << "Topological Order: ";
        while (!stk.empty()) {
            int u = stk.top();
            stk.pop();
            cout << u << " ";

            // Decrease in-degree of adjacent vertices
            for (int v = 0; v < V; ++v) {
                if (adjMatrix[u][v] == 1) {
                    --inDegree[v];
                    if (inDegree[v] == 0) {
                        stk.push(v);
                    }
                }
            }
        }
        cout << endl;
    }

    void dfsUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        // Visit all adjacent vertices of v
        for (int i = 0; i < V; ++i) {
            if (adjMatrix[v][i] == 1 && !visited[i]) {
                dfsUtil(i, visited);
            }
        }
    }

    void dfs() {
        vector<bool> visited(V, false);

        cout << "DFS Traversal: ";
        for (int u = 0; u < V; ++u) {
            if (!visited[u]) {
                dfsUtil(u, visited);
            }
        }
        cout << endl;
    }
};

int main() {
    Graph g(6); // Create a graph with 6 vertices

    // Add directed edges
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    // Perform topological sorting
    g.topologicalSort();

    // Perform DFS traversal
    g.dfs();

    return 0;
}

// Time Complexity:
// Topological Sort: O(V^2)
// DFS Traversal: O(V^2)
