// Given a directed acyclic graph,
// a. write a program for topological ordering of vertices
// b. BFS traversal:

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adjList;

public:
    Graph(int vertices) : V(vertices) {
        // Initialize adjacency list with V vectors
        adjList.resize(V);
    }

    // Add a directed edge from vertex u to vertex v
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    // Topological Sorting using Kahn's algorithm
    vector<int> topologicalSort() {
        vector<int> inDegree(V, 0); // Store in-degrees of vertices
        vector<int> topoOrder; // Store the topological order
        queue<int> q;

        // Calculate in-degrees of all vertices
        for (int u = 0; u < V; ++u) {
            for (int v : adjList[u]) {
                inDegree[v]++;
            }
        }

        // Enqueue vertices with zero in-degree
        for (int u = 0; u < V; ++u) {
            if (inDegree[u] == 0) {
                q.push(u);
            }
        }

        // Perform topological sorting
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topoOrder.push_back(u);

            // Reduce in-degree of adjacent vertices
            for (int v : adjList[u]) {
                if (--inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // Check if all vertices were visited
        if (topoOrder.size() != V) {
            cout << "Graph has a cycle. Topological sorting not possible." << endl;
            return {};
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

            for (int v : adjList[u]) {
                if (!visited[v]) {
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

    // Add directed edges to the graph
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
