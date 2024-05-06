// You have a business with several offices; you want to lease phone lines to connect them up
// with each other; and the phone company charges different amounts of money to connect
// different pairs of cities. You want a set of lines that connects all your offices with a minimum
// total cost. Solve the problem by suggesting appropriate data structures (Prim’s algorithm)

#include <bits/stdc++.h>
using namespace std;

class Graph{
    int node;
    vector<vector<int>> adj;
    vector<bool> visited;

    public:
    Graph(int node){
        this->node=node;
        adj.resize(node+1, vector<int>(node+1, 0));
        visited.resize(node, false);
    }

    void addEdge(int u, int v, int w){
        adj[u][v]=w;
        adj[v][u]=w;
    }

    void Prims(){
        vector<int> parent(node, -1);
        vector<int> key(node, INT_MAX);
        vector<bool> mst(node, false);

        key[0]=0;
        parent[0]=-1;

        for(int i=0; i<node-1; i++){
            int minKey=INT_MAX, u;
            for(int j=0; j<node; j++){
                if(!mst[j] && key[j]<minKey){
                    minKey=key[j];
                    u=j;
                }
            }

            mst[u]=true;

            for(int v=0; v<node; v++){
                if(adj[u][v] && !mst[v] && adj[u][v]<key[v]){
                    parent[v]=u;
                    key[v]=adj[u][v];
                }
            }
        }

        for(int i=1; i<node; i++){
            cout<<parent[i]<<" - "<<i<<" "<<adj[i][parent[i]]<<endl;
        }
    }
};

int main(){
    int n;
    cout<<"Enter no of nodes: ";
    cin>>n;
    Graph G(n);
    int u, v, w;
    cout<<"Enter the edges and their weights: ";
    for(int i=0; i<n; i++){
        cin>>u>>v>>w;
        G.addEdge(u, v, w);
    }

    G.Prims();
    return 0;
}

// Input
// Enter no of nodes: 5
// Enter the edges and their weights: 0 1 2
// 0 3 6
// 1 2 3
// 1 3 8
// 1 4 5
// 2 4 7

// Output
// 0 - 1 2
// 1 - 2 3
// 0 - 3 6
// 1 - 4 5

// Time complexity: O(V^2)
// Space complexity: O(V^2)
// where V is the number of vertices in the graph
// The time complexity of the Prim's algorithm is O(V^2) for the adjacency matrix representation of the graph.
// The space complexity of the Prim's algorithm is O(V^2) for the adjacency matrix representation of the graph.