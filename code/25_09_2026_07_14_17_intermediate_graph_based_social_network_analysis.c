#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct to represent a graph node
typedef struct Node {
    int id;
    int connections[10]; // assume maximum of 10 connections per node
    int numConnections;
} Node;

// Function to add an edge between two nodes in the graph
void addEdge(Node* nodes[], int source, int dest) {
    for (int i = 0; i < nodes[source]->numConnections; i++) {
        if (nodes[source]->connections[i] == dest) {
            return; // edge already exists
        }
    }

    for (int i = 0; i < 10; i++) { // shift existing connections to make room for new one
        if (nodes[source]->connections[i] != -1) {
            nodes[source]->connections[i+1] = nodes[source]->connections[i];
        } else {
            break;
        }
    }

    nodes[source]->connections[0] = dest;
    nodes[source]->numConnections++;
}

// Function to print the graph
void printGraph(Node* nodes[], int numNodes) {
    for (int i = 0; i < numNodes; i++) {
        printf("Node %d: ", i);
        for (int j = 0; j < nodes[i]->numConnections; j++) {
            printf("%d ", nodes[i]->connections[j]);
        }
        printf("\n");
    }
}

// Function to perform a breadth-first search on the graph
void bfs(Node* nodes[], int start, int numNodes) {
    bool visited[numNodes];
    memset(visited, 0, sizeof(bool) * numNodes);

    int queue[numNodes];
    int front = 0;
    int rear = 0;

    printf("BFS traversal starting from node %d:\n", start);
    while (front <= rear) {
        for (int i = front; i <= rear; i++) {
            int current = queue[i];
            visited[current] = true;
            printf("%d ", current);

            // Add unvisited neighbors to the queue
            for (int j = 0; j < nodes[current]->numConnections; j++) {
                int neighbor = nodes[current]->connections[j];
                if (!visited[neighbor]) {
                    queue[++rear] = neighbor;
                }
            }
        }

        front++;
    }
    printf("\n");
}

// Function to perform a depth-first search on the graph
void dfs(Node* nodes[], int start, int numNodes) {
    bool visited[numNodes];
    memset(visited, 0, sizeof(bool) * numNodes);

    printf("DFS traversal starting from node %d:\n", start);
    dfsHelper(nodes, start, visited, &numNodes);

    printf("\n");
}

// Helper function for DFS
void dfsHelper(Node* nodes[], int current, bool visited[], int* numNodes) {
    visited[current] = true;
    printf("%d ", current);

    // Recursively visit unvisited neighbors
    for (int i = 0; i < nodes[current]->numConnections; i++) {
        int neighbor = nodes[current]->connections[i];
        if (!visited[neighbor]) {
            dfsHelper(nodes, neighbor, visited, numNodes);
        }
    }
}

// Main function
int main() {
    // Create sample graph data
    Node* nodes[5];
    for (int i = 0; i < 5; i++) {
        nodes[i] = malloc(sizeof(Node));
        nodes[i]->id = i;
        nodes[i]->numConnections = 0;

        if (i == 0) {
            addEdge(nodes, 0, 1);
            addEdge(nodes, 0, 2);
        } else if (i == 1) {
            addEdge(nodes, 1, 0);
            addEdge(nodes, 1, 3);
        } else if (i == 2) {
            addEdge(nodes, 2, 0);
            addEdge(nodes, 2, 4);
        } else if (i == 3) {
            addEdge(nodes, 3, 1);
        } else if (i == 4) {
            addEdge(nodes, 4, 2);
        }
    }

    // Print the graph
    printGraph(nodes, 5);

    // Perform BFS and DFS traversals
    bfs(nodes, 0, 5);
    dfs(nodes, 0, 5);

    // Free memory
    for (int i = 0; i < 5; i++) {
        free(nodes[i]);
    }

    return 0;
}