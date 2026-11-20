#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <limits>
#include <unordered_map>

using namespace std;

// Define a struct to represent a graph node
struct Node {
    int id;
    vector<pair<int, double>> neighbors; // (neighbor_id, edge_weight)
};

// Define a class for the Dijkstra's algorithm implementation
class Dijkstra {
public:
    map<Node*, double> dijkstra(Node* start, Node* end) {
        priority_queue<pair<double, Node*>, vector<pair<double, Node*> >, greater<pair<double, Node*> > > pq;
        pq.push(make_pair(0.0, start));
        map<Node*, double> distances;

        while (!pq.empty()) {
            pair<double, Node*> p = pq.top();
            pq.pop();

            Node* node = p.second;
            double dist = p.first;

            if (distances.find(node) != distances.end())
                continue;

            if (node == end)
                break;

            for (auto& neighbor : node->neighbors) {
                Node* neighbor_node = &nodes[neighbor.first];
                double edge_dist = neighbor.second;
                double new_distance = dist + edge_dist;

                if (!distances.count(neighbor_node)) {
                    distances[neighbor_node] = new_distance;
                    pq.push(make_pair(new_distance, neighbor_node));
                } else if (new_distance < distances[neighbor_node]) {
                    distances[neighbor_node] = new_distance;
                    pq.push(make_pair(new_distance, neighbor_node));
                }
            }
        }

        return distances;
    }

    // Constructor to initialize the nodes
    Dijkstra(vector<Node> nodes) : nodes(nodes) {}

private:
    vector<Node> nodes;
};

// Function to print the shortest path using the distance map
void print_path(map<Node*, double> distances, Node* start, Node* end) {
    stack<Node*> path;

    for (Node* node = end; node != start; ) {
        if (!distances.count(node))
            return;

        for (auto& neighbor : nodes[node->id].neighbors) {
            Node* neighbor_node = &nodes[neighbor.first];
            double dist = distances[neighbor_node];

            if (dist == distances[node] - 1.0) {
                path.push(neighbor_node);
                node = neighbor_node;
                break;
            }
        }
    }

    while (!path.empty()) {
        cout << path.top()->id << " ";
        path.pop();
    }
    cout << endl;
}

int main() {
    vector<Node> nodes({
        {0, {{1, 4}, {2, 3}}},
        {1, {{2, 2}}},
        {2, {{0, 3}, {1, 2}, {3, 5}}},
        {3, {{2, 5}}}
    });

    Dijkstra dijkstra(nodes);

    map<Node*, double> distances = dijkstra.start(&nodes[0], &nodes[3]);
    print_path(distances, &nodes[0], &nodes[3]);

    return 0;
}
