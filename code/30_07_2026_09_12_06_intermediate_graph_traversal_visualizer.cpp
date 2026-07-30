#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

struct Node {
    int id;
    vector<Node*> neighbors;
};

class GraphTraversalVisualizer {
public:
    GraphTraversalVisualizer(int numNodes, int numEdges) : nodes(numNodes), edges(numEdges) {}

    void addNode(int id) {
        nodes[id] = new Node{id};
    }

    void addEdge(int from, int to) {
        nodes[from]->neighbors.push_back(nodes[to]);
        nodes[to]->neighbors.push_back(nodes[from]);
    }

    void visualizeDFS(Node* start, vector<bool>& visited) {
        stack<Node*> traversal;
        traversal.push(start);

        while (!traversal.empty()) {
            Node* current = traversal.top();
            traversal.pop();

            if (visited[current->id]) continue;

            visited[current->id] = true;

            Text text("DFS: " + to_string(current->id), 24);
            text.setPosition(10, 20 * current->id);
            window.draw(text);

            for (Node* neighbor : current->neighbors) {
                if (!visited[neighbor->id]) {
                    traversal.push(neighbor);
                }
            }
        }
    }

    void visualizeBFS(Node* start, vector<bool>& visited) {
        queue<Node*> traversal;
        traversal.push(start);

        while (!traversal.empty()) {
            Node* current = traversal.front();
            traversal.pop();

            if (visited[current->id]) continue;

            visited[current->id] = true;

            Text text("BFS: " + to_string(current->id), 24);
            text.setPosition(10, 20 * current->id);
            window.draw(text);

            for (Node* neighbor : current->neighbors) {
                if (!visited[neighbor->id]) {
                    traversal.push(neighbor);
                }
            }
        }
    }

private:
    vector<Node*> nodes;
    vector<Edge> edges;

    RenderWindow window(VideoMode(800, 600), "Graph Traversal Visualizer");
};

int main() {
    GraphTraversalVisualizer visualizer(10, 15);

    for (int i = 0; i < 10; ++i) {
        visualizer.addNode(i);
    }

    vector<Edge> edges = {
        {0, 1}, {0, 2}, {1, 3}, {1, 4},
        {2, 5}, {2, 6}, {3, 7}, {4, 8},
        {5, 9}
    };

    for (const auto& edge : edges) {
        visualizer.addEdge(edge.from, edge.to);
    }

    vector<bool> visited(10, false);

    Node* start = visualizer.nodes[0];

    while (!window.pollEvent(event)) {}

    visualizer.visualizeDFS(start, visited);

    return 0;
}