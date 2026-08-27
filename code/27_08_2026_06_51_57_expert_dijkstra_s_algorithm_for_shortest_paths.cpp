#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

// Define a struct to represent graph nodes
struct Node {
    int id;
    vector<pair<int, int>> edges; // (neighbor_id, weight)
};

// Function to perform Dijkstra's algorithm
void dijkstra(const vector<Node>& graph, int start, int end) {
    unordered_map<int, int> distance; // Distance from start to node
    unordered_map<int, int> previous; // Previous node in shortest path
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Initialize distances and previous nodes
    for (const auto& node : graph) {
        distance[node.id] = INT_MAX;
        previous[node.id] = -1; // -1 indicates not visited yet
    }
    distance[start] = 0; // Distance to start node is 0

    // Create priority queue with start node
    pq.push({0, start});

    while (!pq.empty()) {
        int current_node_id = pq.top().second;
        int current_distance = pq.top().first;
        pq.pop();

        if (current_distance > distance[current_node_id]) continue; // Skip visited nodes

        for (const auto& edge : graph[current_node_id].edges) {
            int neighbor_id = edge.first;
            int weight = edge.second;

            // Calculate new distance to neighbor node
            int new_distance = current_distance + weight;

            if (new_distance < distance[neighbor_id]) {
                distance[neighbor_id] = new_distance;
                previous[neighbor_id] = current_node_id; // Update previous node in path
                pq.push({new_distance, neighbor_id}); // Add to priority queue
            }
        }
    }

    // Print shortest path from start to end
    int current_node = end;
    while (current_node != -1) {
        cout << current_node << " ";
        current_node = previous[current_node];
    }
    cout << endl;
}

int main() {
    vector<Node> graph = {
        {0, {{1, 4}, {2, 5}}},
        {1, {{2, 3}, {3, 2}}},
        {2, {{3, 6}, {4, 7}}},
        {3, {{4, 8}, {5, 9}}},
        {4, {{5, 10}}}
    };

    dijkstra(graph, 0, 4);

    return 0;
}
