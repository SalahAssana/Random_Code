#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// Define a struct to represent nodes in the graph
struct Node {
    string id;
    vector<string> neighbors;
};

// Define a class to represent the graph
class Graph {
public:
    map<string, Node> nodes;

    // Add a node to the graph
    void addNode(string id) {
        nodes[id] = {id, {}};
    }

    // Add an edge between two nodes in the graph
    void addEdge(string from, string to) {
        if (nodes.find(from) != nodes.end() && nodes.find(to) != nodes.end()) {
            nodes[from].neighbors.push_back(to);
            nodes[to].neighbors.push_back(from);
        }
    }

    // Perform a BFS traversal of the graph starting from a given node
    void bfsTraversal(string startNode) {
        if (nodes.find(startNode) == nodes.end()) return;

        vector<string> visited;
        queue<string> q;

        q.push(startNode);
        visited.push_back(startNode);

        while (!q.empty()) {
            string currentNode = q.front();
            q.pop();

            cout << "Visiting node: " << currentNode << endl;

            for (const string& neighbor : nodes[currentNode].neighbors) {
                if (find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                    q.push(neighbor);
                    visited.push_back(neighbor);
                }
            }
        }

        cout << "BFS traversal completed." << endl;
    }
};

int main() {
    Graph graph;

    // Add nodes to the graph
    graph.addNode("Alice");
    graph.addNode("Bob");
    graph.addNode("Charlie");

    // Add edges between nodes in the graph
    graph.addEdge("Alice", "Bob");
    graph.addEdge("Bob", "Charlie");
    graph.addEdge("Alice", "Charlie");

    // Perform a BFS traversal of the graph starting from Alice
    graph.bfsTraversal("Alice");

    return 0;
}