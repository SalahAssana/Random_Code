#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Structure to represent graph edges
struct Edge {
    int from;
    int to;
};

// Function to perform DFS on a graph
void dfs(vector<vector<int>> &graph, vector<bool> &visited, int node) {
    visited[node] = true; // Mark the current node as visited

    cout << "Visiting node " << node << endl;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(graph, visited, neighbor); // Recursively visit unvisited neighbors
        }
    }
}

// Function to perform BFS on a graph
void bfs(vector<vector<int>> &graph, vector<bool> &visited, int start) {
    queue<int> q; // Queue for BFS traversal

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        cout << "Visiting node " << node << endl;

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                q.push(neighbor); // Add unvisited neighbors to the queue
                visited[neighbor] = true;
            }
        }
    }
}

// Function to print the adjacency list representation of a graph
void printGraph(vector<vector<int>> &graph) {
    for (int i = 0; i < graph.size(); i++) {
        cout << "Node " << i << ": ";
        for (int j : graph[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
}

// Main function
int main() {
    // Synthetic data: Create a sample graph with 5 nodes and 7 edges
    vector<vector<int>> graph = {{1, 2}, {0, 3}, {0, 4}, {1, 4}, {3, 4}};
    int numNodes = 5;

    // Initialize visited array for DFS/BFS
    vector<bool> visited(numNodes, false);

    cout << "DFS traversal:" << endl;
    dfs(graph, visited, 0); // Start DFS from node 0

    cout << "\nBFS traversal:" << endl;
    for (int i = 0; i < numNodes; i++) {
        fill(visited.begin(), visited.end(), false);
        bfs(graph, visited, i); // Start BFS from each node
    }

    return 0;
}
