#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Define a struct to represent a graph node
struct Node {
    int id;
    vector<Node*> neighbors; // Adjacent nodes
};

// Function to perform DFS traversal
void dfsTraversal(Node* startNode, vector<bool>& visited) {
    cout << "DFS Traversal: ";
    queue<Node*> q;
    q.push(startNode);
    while (!q.empty()) {
        Node* currentNode = q.front();
        q.pop();
        if (!visited[currentNode->id]) {
            visited[currentNode->id] = true;
            cout << currentNode->id << " ";
            for (auto neighbor : currentNode->neighbors) {
                if (!visited[neighbor->id])
                    q.push(neighbor);
            }
        }
    }
    cout << endl;
}

// Function to perform BFS traversal
void bfsTraversal(Node* startNode, vector<bool>& visited) {
    cout << "BFS Traversal: ";
    queue<Node*> q;
    q.push(startNode);
    while (!q.empty()) {
        Node* currentNode = q.front();
        q.pop();
        if (!visited[currentNode->id]) {
            visited[currentNode->id] = true;
            cout << currentNode->id << " ";
            for (auto neighbor : currentNode->neighbors) {
                if (!visited[neighbor->id])
                    q.push(neighbor);
            }
        }
    }
    cout << endl;
}

int main() {
    // Create a sample graph
    vector<Node*> nodes = {};
    Node* node1 = new Node();
    node1->id = 0;
    nodes.push_back(node1);

    Node* node2 = new Node();
    node2->id = 1;
    nodes.push_back(node2);

    Node* node3 = new Node();
    node3->id = 2;
    nodes.push_back(node3);

    Node* node4 = new Node();
    node4->id = 3;
    nodes.push_back(node4);

    node1->neighbors.push_back(node2);
    node1->neighbors.push_back(node3);
    node2->neighbors.push_back(node4);
    node3->neighbors.push_back(node4);

    // Perform DFS and BFS traversal
    vector<bool> visited(nodes.size(), false);
    dfsTraversal(node1, visited);
    bfsTraversal(node1, visited);

    return 0;
}