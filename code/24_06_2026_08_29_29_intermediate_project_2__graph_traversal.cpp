#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    int source;
    int destination;
};

class Graph {
public:
    vector<vector<int>> adjList;
    int V;

    void addEdge(int v, int w) {
        adjList[v].push_back(w);
        adjList[w].push_back(v); // for undirected graph
    }

    void DFSUtil(int v, bool visited[]) {
        cout << v << " ";
        visited[v] = true;
        vector<int>::iterator i;
        for (i = adjList[v].begin(); i != adjList[v].end(); ++i) {
            if (!visited[*i])
                DFSUtil(*i, visited);
        }
    }

    void DFS(int v) {
        bool visited[V];
        for (int i = 0; i < V; ++i)
            visited[i] = false;

        DFSUtil(v, visited);
    }

    void BFS(int s) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[s] = true;
        cout << s << " ";

        q.push(s);

        while (!q.empty()) {
            int temp = q.front();
            q.pop();

            for (int i = 0; i < V; ++i) {
                if (!visited[i] && adjList[temp].count(i)) {
                    visited[i] = true;
                    cout << i << " ";
                    q.push(i);
                }
            }
        }
    }
};

int main() {
    int V = 5;
    Graph g(V);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    cout << "DFS Traversal: ";
    g.DFS(0);
    cout << endl;

    cout << "BFS Traversal: ";
    g.BFS(0);
    cout << endl;

    return 0;
}