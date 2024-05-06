// 	Implement Dijkstra’s algorithm for shortest path between a given pair of vertices.
// Test your program for following example:
// Given a directed acyclic graph,
// a. write a program for topological ordering of vertices
// b. DFS traversal 

#include <bits/stdc++.h>
using namespace std;

class Graph {
    int node;
    vector<pair<int, int>> adj[100];
    vector<int> parent;

public:
    Graph(int node) {
        this->node = node;
        parent.resize(node);
        for (int i = 0; i < node; i++) {
            parent[i] = i;
        }
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
    }

    void Dijkstra(int src, int dest) {
        vector<int> dist(node, INT_MAX);
        vector<int> path(node, -1);
        dist[src] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;

                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    path[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Shortest path from " << src << " to " << dest << " is: ";
        int tmp = dest;
        stack<int> s;
        while (tmp != -1) {
            s.push(tmp);
            tmp = path[tmp];
        }

        while (!s.empty()) {
            cout << s.top() << " ";
            s.pop();
        }
        cout << endl;
    }
};

int main() {
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;

    Graph g(n);

    int e;
    cout << "Enter the number of edges: ";
    cin >> e;

    for (int i = 0; i < e; i++) {
        int u, v, w;
        cout << "Enter the source, destination and weight of edge " << i + 1 << ": ";
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int src, dest;
    cout << "Enter the source and destination: ";
    cin >> src >> dest;

    g.Dijkstra(src, dest);

    return 0;
}

// Output
// Enter the number of nodes: 6
// Enter the number of edges: 8
// Enter the source, destination and weight of edge 1: 0 1 2
// Enter the source, destination and weight of edge 2: 0 2 3
// Enter the source, destination and weight of edge 3: 1 2 8
// Enter the source, destination and weight of edge 4: 1 3 5
// Enter the source, destination and weight of edge 5: 2 3 1
// Enter the source, destination and weight of edge 6: 2 4 4
// Enter the source, destination and weight of edge 7: 3 4 7
// Enter the source, destination and weight of edge 8: 3 5 6
// Enter the source and destination: 0 5

// Output
// Shortest path from 0 to 5 is: 0 2 3 5

// Time Complexity
// Dijkstra's algorithm has a time complexity of O(V^2) for adjacency matrix representation and O(E + V log V) for adjacency list representation. Here, we are using an adjacency list representation, so the time complexity of the algorithm is O(E + V log V).


