// You have a business with several offices; you want to lease phone lines to connect them up
// with each other; and the phone company charges different amounts of money to connect
// different pairs of cities. You want a set of lines that connects all your offices with a minimum
// total cost. Solve the problem by suggesting appropriate data structures (Kruskal’s algorithm)

#include <bits/stdc++.h>
using namespace std;

class Graph{
    int node;
    vector<pair<int, pair<int, int>>> edges;
    vector<int> parent;

    public:
    Graph(int node){
        this->node=node;
        parent.resize(node);
        for(int i=0; i<node; i++){
            parent[i]=i;
        }
    }

    void addEdge(int u, int v, int w){
        edges.push_back({w, {u, v}});
    }

    int find(int i){
        if(parent[i]==i){
            return i;
        }
        return find(parent[i]);
    }

    void Union(int i, int j){
        int a=find(i);
        int b=find(j);
        parent[a]=b;
    }

    void Kruskal(){
        sort(edges.begin(), edges.end());
        int cost=0;
        for(auto edge: edges){
            int w=edge.first;
            int u=edge.second.first;
            int v=edge.second.second;

            if(find(u)!=find(v)){
                cout<<u<<" - "<<v<<" "<<w<<endl;
                cost+=w;
                Union(u, v);
            }
        }
        cout<<"Total cost: "<<cost<<endl;
    }
};

int main(){
    int n;
    cout<<"Enter the number of nodes: ";
    cin>>n;

    Graph g(n);

    int e;
    cout<<"Enter the number of edges: ";
    cin>>e;

    cout<<"Enter the edges (u v w):"<<endl;
    for(int i=0; i<e; i++){
        int u, v, w;
        cin>>u>>v>>w;
        g.addEdge(u, v, w);
    }

    g.Kruskal();

    return 0;
}

// Input:
// Enter the number of nodes: 6
// Enter the number of edges: 8
// Enter the edges (u v w):
// 0 1 2
// 0 2 3
// 1 2 8
// 1 3 5
// 2 3 1
// 2 4 4
// 3 4 7
// 3 5 6

// Output:
// 2 - 3 1
// 0 - 1 2
// 0 - 2 3
// 2 - 4 4
// 3 - 5 6
// Total cost: 16

// Time complexity: O(E log E) where E is the number of edges in the graph

