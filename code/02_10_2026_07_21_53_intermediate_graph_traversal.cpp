#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int v1;
    int v2;
};

class Graph {
public:
    // Constructor to initialize the graph with vertices and edges
    Graph(int V, vector<Edge>& E) : V(V), E(E), visited(V, false) {}

    // Function to perform DFS traversal on the graph
    void DFS(int v) {
        stack<int> s;
        s.push(v);
        while (!s.empty()) {
            int u = s.top();
            s.pop();
            if (!visited[u]) {
                cout << "Visiting vertex: " << u << endl;
                visited[u] = true;
                for (Edge& e : E) {
                    if (e.v1 == u && !visited[e.v2])
                        s.push(e.v2);
                    else if (e.v2 == u && !visited[e.v1])
                        s.push(e.v1);
                }
            }
        }
    }

private:
    int V;
    vector<Edge> E;
    vector<bool> visited;
};

int main() {
    // Synthetic data for the graph
    vector<Edge> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 4}};
    Graph g(5, edges);

    // Perform DFS traversal on the graph
    for (int i = 0; i < g.V; ++i) {
        if (!g.visited[i]) {
            g.DFS(i);
            cout << endl;
        }
    }

    return 0;
}