// Write a program to represent input graph using adjacency matrix. Implement Depth First and Breadth first traversal algorithms. Check if graph is connected, if not find how many connected components it has.
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adjMatrix;

public:
    Graph(int vertices) : V(vertices) {
        // Initialize adjacency matrix with V x V dimensions
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    // Add an edge between vertices u and v
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // For undirected graph
    }

    // Depth First Search (DFS) traversal
    void DFS(int startVertex) {
        vector<bool> visited(V, false);
        stack<int> stack;

        stack.push(startVertex);
        visited[startVertex] = true;

        cout << "DFS Traversal starting from vertex " << startVertex << ": ";
        while (!stack.empty()) {
            int current = stack.top();
            stack.pop();
            cout << current << " ";

            // Visit all adjacent vertices
            for (int i = 0; i < V; ++i) {
                if (adjMatrix[current][i] == 1 && !visited[i]) {
                    stack.push(i);
                    visited[i] = true;
                }
            }
        }
        cout << endl;
    }

    // Breadth First Search (BFS) traversal
    void BFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> queue;

        queue.push(startVertex);
        visited[startVertex] = true;

        cout << "BFS Traversal starting from vertex " << startVertex << ": ";
        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();
            cout << current << " ";

            // Visit all adjacent vertices
            for (int i = 0; i < V; ++i) {
                if (adjMatrix[current][i] == 1 && !visited[i]) {
                    queue.push(i);
                    visited[i] = true;
                }
            }
        }
        cout << endl;
    }

    // Check if the graph is connected using DFS
    bool isConnected() {
        vector<bool> visited(V, false);
        DFS(0); // Perform DFS traversal starting from vertex 0

        // Check if all vertices are visited
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                return false;
            }
        }
        return true;
    }

    // Find the number of connected components using DFS
    int countConnectedComponents() {
        vector<bool> visited(V, false);
        int count = 0;

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                DFS(i); // Perform DFS traversal starting from each unvisited vertex
                ++count;
            }
        }
        return count;
    }
};

int main() {
    // Create a graph with 6 vertices
    Graph graph(6);

    // Add edges to the graph
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);

    // Perform DFS and BFS traversal
    graph.DFS(0);
    graph.BFS(0);

    // Check if the graph is connected
    if (graph.isConnected()) {
        cout << "The graph is connected." << endl;
    } else {
        cout << "The graph is not connected." << endl;
        int components = graph.countConnectedComponents();
        cout << "Number of connected components: " << components << endl;
    }

    return 0;
}
