#include <iostream>
#include <vector>
#include <queue>

// Structure to represent a graph node
struct Node {
    int id;
    std::vector<int> neighbors;
};

// Function to perform BFS traversal on a graph
void bfsTraversal(Node* nodes, int startNode) {
    // Create a queue for BFS and enqueue the starting node
    std::queue<int> q;
    q.push(startNode);

    // Mark all nodes as not visited
    bool* visited = new bool[nodes->size()];
    for (int i = 0; i < nodes->size(); ++i) {
        visited[i] = false;
    }

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();

        if (!visited[currentNode]) {
            std::cout << "Visiting node " << currentNode << std::endl;

            // Mark the current node as visited
            visited[currentNode] = true;

            // Enqueue all unvisited neighbors of the current node
            for (int neighbor : nodes->at(currentNode).neighbors) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                }
            }
        }
    }

    delete[] visited;
}

// Function to perform DFS traversal on a graph
void dfsTraversal(Node* nodes, int startNode) {
    // Create a recursive function for DFS traversal
    void dfsHelper(int node) {
        std::cout << "Visiting node " << node << std::endl;

        // Mark the current node as visited
        bool visited = false;
        for (int i = 0; i < nodes->size(); ++i) {
            if (nodes->at(i).id == node) {
                visited = true;
                break;
            }
        }

        if (!visited) {
            // Recur for all the adjacent vertices of the current node
            for (int neighbor : nodes->at(node).neighbors) {
                dfsHelper(neighbor);
            }
        }
    }

    // Start DFS traversal from the given start node
    dfsHelper(startNode);
}

// Function to print the adjacency list representation of a graph
void printGraph(Node* nodes) {
    for (int i = 0; i < nodes->size(); ++i) {
        std::cout << "Node " << i << ": ";
        for (int neighbor : nodes->at(i).neighbors) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}

// Function to create a graph from a given adjacency list
Node* createGraph(int numNodes, const int* edges[]) {
    Node* nodes = new Node[numNodes];

    for (int i = 0; i < numNodes; ++i) {
        nodes[i].id = i;
    }

    for (int i = 0; i < numNodes; ++i) {
        for (int j = edges[i]; j < edges[i + 1]; ++j) {
            int neighbor = j % numNodes;
            nodes[i].neighbors.push_back(neighbor);
        }
    }

    return nodes;
}

int main() {
    // Define the number of nodes in the graph
    int numNodes = 6;

    // Define the edges in the graph (adjacency list representation)
    const int* edges = new int[numNodes + 1];
    edges[0] = 0;
    edges[1] = 1;
    edges[2] = 2;
    edges[3] = 4;
    edges[4] = 5;
    edges[5] = 6;

    // Create the graph from the given adjacency list
    Node* nodes = createGraph(numNodes, edges);

    // Print the adjacency list representation of the graph
    printGraph(nodes);

    // Perform BFS traversal on the graph starting from node 0
    bfsTraversal(nodes, 0);

    // Perform DFS traversal on the graph starting from node 0
    dfsTraversal(nodes, 0);

    delete[] nodes;
    return 0;
}