#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define a structure to represent a graph node
typedef struct {
    int id;
    int visited;
    struct Node* neighbors[10]; // Assume at most 10 neighbors
} Node;

// Function to perform BFS traversal
void bfs(Node* start, int numNodes) {
    int visited[numNodes];
    for (int i = 0; i < numNodes; i++) {
        visited[i] = 0;
    }

    int queue[numNodes];
    int front = 0, rear = 0;

    // Mark the starting node as visited and enqueue it
    Node* current = start;
    visited[current->id - 1] = 1;
    while (front <= rear) {
        // Dequeue a vertex from the queue and print it
        printf("%d ", current->id);
        for (int i = 0; i < 10 && current->neighbors[i]; i++) {
            Node* neighbor = current->neighbors[i];
            if (!visited[neighbor->id - 1]) {
                // If this is the first time we've seen a node, mark it as visited and enqueue it
                visited[neighbor->id - 1] = 1;
                queue[++rear] = neighbor->id;
            }
        }

        // Move to the next vertex in the queue
        front++;
        current = start;
        for (int i = front; i <= rear; i++) {
            if (queue[i] == current->id) {
                current = current;
                break;
            }
        }
    }
    printf("\n");
}

// Function to create a graph node
Node* newNode(int id) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->id = id;
    for (int i = 0; i < 10; i++) {
        new_node->neighbors[i] = NULL;
    }
    return new_node;
}

// Function to add an edge between two nodes
void addEdge(Node* node1, Node* node2) {
    for (int i = 0; i < 10; i++) {
        if (!node1->neighbors[i]) {
            node1->neighbors[i] = node2;
            break;
        }
    }
}

// Function to print the graph
void printGraph(Node* start, int numNodes) {
    for (int i = 0; i < numNodes; i++) {
        Node* current = start + i;
        printf("%d:", current->id);
        for (int j = 0; j < 10 && current->neighbors[j]; j++) {
            printf(" %d", current->neighbors[j]->id);
        }
        printf("\n");
    }
}

int main() {
    // Create the graph nodes
    Node* start = newNode(1);
    Node* node2 = newNode(2);
    Node* node3 = newNode(3);
    Node* node4 = newNode(4);
    Node* node5 = newNode(5);

    // Add edges to the graph
    addEdge(start, node2);
    addEdge(start, node3);
    addEdge(node2, node4);
    addEdge(node3, node5);

    // Print the graph
    printGraph((Node*)start, 5);

    // Perform BFS traversal starting from node 1
    bfs(start, 5);

    return 0;
}