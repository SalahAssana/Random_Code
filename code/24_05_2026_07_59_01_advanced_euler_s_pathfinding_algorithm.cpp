#include <iostream>
#include <vector>
#include <queue>
#include <limits>

// Graph representation using adjacency list
struct Graph {
    std::vector<std::vector<int>> edges;
};

// Euler's Pathfinding Algorithm implementation
Graph eulerPath(Graph& graph, int start, int end) {
    // Initialize variables
    int n = graph.edges.size();
    bool visited[n];
    for (int i = 0; i < n; ++i)
        visited[i] = false;

    // Reset edges count
    std::vector<int> inDeg(n);
    for (const auto& edge : graph.edges)
        for (const int &node : edge)
            ++inDeg[node];

    // Start BFS from start node
    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    Graph eulerPathGraph;
    while (!q.empty()) {
        int currNode = q.front();
        q.pop();

        // Process current node
        for (const auto& edge : graph.edges[currNode]) {
            --inDeg[edge];
            if (!visited[edge] && inDeg[edge] == 0) {
                eulerPathGraph.edges.push_back({currNode, edge});
                q.push(edge);
                visited[edge] = true;
            }
        }
    }

    // Check for Euler Path existence
    bool hasEulerPath = true;
    for (int i = 0; i < n; ++i)
        if (inDeg[i])
            hasEulerPath = false;

    return hasEulerPath ? eulerPathGraph : Graph{};
}

// Main function
int main() {
    // Define the graph as an adjacency list representation
    Graph graph;
    graph.edges.push_back({1, 2});
    graph.edges.push_back({2, 3});
    graph.edges.push_back({3, 4});
    graph.edges.push_back({4, 5});
    graph.edges.push_back({5, 6});
    graph.edges.push_back({6, 7});
    graph.edges.push_back({1, 7});

    // Start node and end node
    int start = 1;
    int end = 7;

    // Run Euler's Pathfinding Algorithm
    Graph eulerPathGraph = eulerPath(graph, start, end);

    // Print the Euler Path Graph edges
    for (const auto& edge : eulerPathGraph.edges)
        std::cout << "Edge: (" << edge[0] << ", " << edge[1] << ")" << std::endl;

    return 0;
}