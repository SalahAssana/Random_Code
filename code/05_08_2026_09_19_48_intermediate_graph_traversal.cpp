#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Graph structure
struct Edge {
    int v1;
    int v2;
    int weight;
};

class Graph {
public:
    vector<Edge> edges;
    int V;

    // Constructor
    Graph(int V) : V(V) {}

    void addEdge(int v1, int v2, int weight) {
        Edge e = {v1, v2, weight};
        edges.push_back(e);
    }

    // BFS function to find shortest path
    vector<int> BFS(int start, int end) {
        vector<int> parent(V, -1);
        vector<int> dist(V, numeric_limits<int>::max());
        queue<pair<int, int>> q;

        dist[start] = 0;
        q.push({start, 0});

        while (!q.empty()) {
            pair<int, int> front = q.front();
            q.pop();

            if (front.first == end) {
                break;
            }

            for (Edge e : edges) {
                if (e.v1 == front.first && dist[e.v2] > dist[front.first] + e.weight) {
                    dist[e.v2] = dist[front.first] + e.weight;
                    parent[e.v2] = front.first;
                    q.push({e.v2, dist[e.v2]});
                }
            }
        }

        vector<int> path;
        int current = end;

        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }

        reverse(path.begin(), path.end());
        return path;
    }

    // DFS function to find shortest path
    vector<int> DFS(int start, int end) {
        vector<int> visited(V, false);
        vector<int> dist(V, numeric_limits<int>::max());
        vector<int> parent(V, -1);

        queue<pair<int, int>> q;

        visited[start] = true;
        dist[start] = 0;
        q.push({start, 0});

        while (!q.empty()) {
            pair<int, int> front = q.front();
            q.pop();

            if (front.first == end) {
                break;
            }

            for (Edge e : edges) {
                if (e.v1 == front.first && !visited[e.v2] && dist[e.v2] > dist[front.first] + e.weight) {
                    visited[e.v2] = true;
                    dist[e.v2] = dist[front.first] + e.weight;
                    parent[e.v2] = front.first;
                    q.push({e.v2, dist[e.v2]});
                }
            }
        }

        vector<int> path;
        int current = end;

        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }

        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    Graph graph(5);
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 2, 4);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 4, 2);

    vector<int> bfsPath = graph.BFS(0, 4);
    cout << "BFS Path: ";
    for (int v : bfsPath) {
        cout << v << " ";
    }
    cout << endl;

    vector<int> dfsPath = graph.DFS(0, 4);
    cout << "DFS Path: ";
    for (int v : dfsPath) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}