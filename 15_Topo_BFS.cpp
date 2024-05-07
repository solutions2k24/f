// Given a directed acyclic graph,
// a. write a program for topological ordering of vertices
// b. BFS traversal:

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
        // Initialize adjacency matrix with size VxV and set all values to 0
        adjMatrix.assign(V, vector<int>(V, 0));
    }

    // Add a directed edge from vertex u to vertex v
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
    }

    // Recursive function for topological sorting
    void topologicalSortUtil(int v, vector<bool>& visited, stack<int>& stk) {
        visited[v] = true;

        // Recursively visit all adjacent vertices
        for (int i = 0; i < V; ++i) {
            if (adjMatrix[v][i] && !visited[i]) {
                topologicalSortUtil(i, visited, stk);
            }
        }

        // Push current vertex to stack after visiting all adjacent vertices
        stk.push(v);
    }

    // Topological Sorting using recursion
    vector<int> topologicalSort() {
        vector<bool> visited(V, false);
        stack<int> stk;

        // Perform topological sorting for each vertex that has not been visited
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, stk);
            }
        }

        // Collect vertices in topological order from stack
        vector<int> topoOrder;
        while (!stk.empty()) {
            topoOrder.push_back(stk.top());
            stk.pop();
        }

        return topoOrder;
    }

    // Breadth First Search (BFS) traversal
    void BFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;

        q.push(startVertex);
        visited[startVertex] = true;

        cout << "BFS Traversal starting from vertex " << startVertex << ": ";
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

            for (int v = 0; v < V; ++v) {
                if (adjMatrix[u][v] && !visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // Create a directed acyclic graph (DAG) with 6 vertices
    Graph graph(6);

    // Add directed edges to the graph using adjacency matrix
    graph.addEdge(5, 2);
    graph.addEdge(5, 0);
    graph.addEdge(4, 0);
    graph.addEdge(4, 1);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);

    // Perform topological sorting
    vector<int> topoOrder = graph.topologicalSort();
    if (!topoOrder.empty()) {
        cout << "Topological Ordering of Vertices: ";
        for (int vertex : topoOrder) {
            cout << vertex << " ";
        }
        cout << endl;
    }

    // Perform BFS traversal starting from vertex 5
    graph.BFS(5);

    return 0;
}


// Time Complexity:
// Topological Sort: O(V^2)
// BFS Traversal: O(V^2)
