#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int node;
    int weight;
};

// Function to perform BFS traversal
void BFS(int start, vector<vector<Edge>>& graph) {
    // Initialize a visited array and a queue
    bool visited[graph.size()];
    fill(visited, visited + graph.size(), false);
    queue<int> q;

    // Add the starting node to the queue and mark it as visited
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        cout << current << " ";

        for (auto& edge : graph[current]) {
            if (!visited[edge.node]) {
                q.push(edge.node);
                visited[edge.node] = true;
            }
        }
    }
}

int main() {
    // Define the graph using an adjacency list representation
    vector<vector<Edge>> graph = {
        {}, {Edge{1, 2}, Edge{3, 4}}, 
        {Edge{0, 1}}, {Edge{0, 3}}, 
        {Edge{1, 3}}};

    // Perform BFS traversal starting from node 0
    BFS(0, graph);

    return 0;
}