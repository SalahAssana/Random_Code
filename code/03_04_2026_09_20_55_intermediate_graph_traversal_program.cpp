#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int start;
    int end;
};

class Graph {
public:
    vector<vector<Edge>> adjList;
    int V;

    // Constructor to initialize the graph
    Graph(int vertices) : V(vertices) {}

    // Function to add an edge to the graph
    void addEdge(int start, int end) {
        Edge edge = {start, end};
        adjList[start].push_back(edge);
    }

    // Breadth-First Search (BFS)
    void BFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int vertex = q.front();
            cout << "Visited: " << vertex << endl;
            q.pop();

            for (auto edge : adjList[vertex]) {
                if (!visited[edge.end]) {
                    visited[edge.end] = true;
                    q.push(edge.end);
                }
            }
        }
    }

    // Depth-First Search (DFS)
    void DFS(int startVertex) {
        vector<bool> visited(V, false);

        stack<int> s;

        visited[startVertex] = true;
        s.push(startVertex);

        while (!s.empty()) {
            int vertex = s.top();
            cout << "Visited: " << vertex << endl;
            s.pop();

            for (auto edge : adjList[vertex]) {
                if (!visited[edge.end]) {
                    visited[edge.end] = true;
                    s.push(edge.end);
                }
            }
        }
    }

    // Dijkstra's algorithm
    void dijkstra(int startVertex) {
        vector<int> distance(V, numeric_limits<int>::max());
        vector<bool> visited(V, false);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        distance[startVertex] = 0;
        pq.push({0, startVertex});

        while (!pq.empty()) {
            auto front = pq.top();
            pq.pop();

            int vertex = front.second;
            if (visited[vertex]) continue;

            visited[vertex] = true;

            for (auto edge : adjList[vertex]) {
                int newDist = distance[vertex] + 1; // Assuming all edges have a weight of 1
                if (newDist < distance[edge.end]) {
                    distance[edge.end] = newDist;
                    pq.push({newDist, edge.end});
                }
            }
        }

        cout << "Shortest distances: ";
        for (int i = 0; i < V; i++) {
            cout << distance[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Graph graph(6);

    // Add edges to the graph
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);

    cout << "BFS: ";
    graph.BFS(0);
    cout << endl;

    cout << "DFS: ";
    graph.DFS(0);
    cout << endl;

    cout << "Dijkstra's algorithm: ";
    graph.dijkstra(0);
    cout << endl;

    return 0;
}