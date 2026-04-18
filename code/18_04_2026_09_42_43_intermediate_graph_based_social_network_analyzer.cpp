#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// Define a struct to represent a graph node
struct GraphNode {
    int id;
    vector<int> neighbors;
};

// Function to perform depth-first search (DFS) on the graph
void DFS(GraphNode* node, map<int, bool>& visited) {
    cout << "Visiting node " << node->id << endl;

    visited[node->id] = true;  // Mark the current node as visited

    for (int neighbor : node->neighbors) {
        if (!visited[neighbor]) {
            DFS(&graphNodes[neighbor], visited);  // Recursively visit unvisited neighbors
        }
    }
}

// Function to generate a random graph with specified number of nodes and edges
vector<GraphNode*> generateRandomGraph(int numNodes, int numEdges) {
    vector<GraphNode*> graphNodes(numNodes);

    for (int i = 0; i < numNodes; i++) {
        graphNodes[i]->id = i;
    }

    // Add random edges to the graph
    srand(time(0));  // Seed the random number generator

    for (int i = 0; i < numEdges; i++) {
        int node1 = rand() % numNodes;
        int node2 = rand() % numNodes;

        while (node1 == node2) {  // Ensure nodes are distinct
            node2 = rand() % numNodes;
        }

        graphNodes[node1]->neighbors.push_back(node2);
        graphNodes[node2]->neighbors.push_back(node1);  // Add edge in both directions
    }

    return graphNodes;
}

// Function to print the adjacency list representation of the graph
void printGraph(const vector<GraphNode*>& graphNodes) {
    for (int i = 0; i < graphNodes.size(); i++) {
        cout << "Node " << graphNodes[i]->id << ": ";
        for (int neighbor : graphNodes[i]->neighbors) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}

int main() {
    int numNodes = 10;  // Number of nodes in the graph
    int numEdges = 20;  // Number of edges in the graph

    vector<GraphNode*> graphNodes = generateRandomGraph(numNodes, numEdges);

    map<int, bool> visited;

    // Perform DFS on the graph
    for (int i = 0; i < numNodes; i++) {
        if (!visited[graphNodes[i]->id]) {
            DFS(graphNodes[i], visited);
        }
    }

    printGraph(graphNodes);

    return 0;
}