#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <limits>

using namespace std;

// A class to represent nodes in the graph
class Node {
public:
    int id;
    vector<Node*> neighbors;
    map<Node*, int> neighborDistances;

    Node(int id) : id(id) {}
};

// Dijkstra's algorithm function
void dijkstra(vector<Node*>& nodes, Node* startNode, Node* endNode) {
    priority_queue<pair<int, Node*>, vector<pair<int, Node*> >, greater<pair<int, Node*>>> pq;
    map<Node*, int> distances;
    map<Node*, Node*> previous;

    // Initialize distances and previous
    for (Node* node : nodes) {
        if (node == startNode) {
            distances[node] = 0;
        } else {
            distances[node] = numeric_limits<int>::max();
        }
        previous[node] = nullptr;
    }

    pq.push(make_pair(0, startNode));

    while (!pq.empty()) {
        Node* currentNode = pq.top()->second;
        pq.pop();

        // If this is the end node, we're done
        if (currentNode == endNode) {
            break;
        }

        for (Node* neighbor : currentNode->neighbors) {
            int distanceToNeighbor = distances[currentNode] + 1; // Assume all edges have equal weight

            if (distanceToNeighbor < distances[neighbor]) {
                distances[neighbor] = distanceToNeighbor;
                previous[neighbor] = currentNode;
                pq.push(make_pair(distanceToNeighbor, neighbor));
            }
        }
    }

    // Print the shortest path
    Node* current = endNode;
    while (current != nullptr) {
        cout << "Node " << current->id << endl;
        current = previous[current];
    }
}

int main() {
    vector<Node*> nodes;

    // Create some nodes
    for (int i = 0; i < 5; i++) {
        Node* node = new Node(i);
        nodes.push_back(node);

        if (i > 0) {
            nodes[i-1]->neighbors.push_back(node);
            nodes[i]->neighbors.push_back(nodes[i-1]);
        }

        // Add some more edges
        if (i % 2 == 0) {
            nodes[(i - 1 + 3) % 5]->neighbors.push_back(node);
            node->neighbors.push_back(nodes[(i - 1 + 3) % 5]);
        }
    }

    Node* startNode = nodes[0];
    Node* endNode = nodes[nodes.size() - 1];

    dijkstra(nodes, startNode, endNode);

    return 0;
}