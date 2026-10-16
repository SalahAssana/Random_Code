#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent a graph node
typedef struct {
    int id;
    int weight; // distance from source node
    struct GraphNode* next;
} GraphNode;

// Define a function to add an edge between two nodes
void addEdge(GraphNode** graph, int src, int dest, int weight) {
    GraphNode* newNode = (GraphNode*) malloc(sizeof(GraphNode));
    newNode->id = dest;
    newNode->weight = weight;
    newNode->next = (*graph)[src];
    (*graph)[src] = newNode;
}

// Define a function to print the graph
void printGraph(GraphNode** graph, int numNodes) {
    for (int i = 0; i < numNodes; i++) {
        GraphNode* node = (*graph)[i];
        printf("Node %d: ", i);
        while (node != NULL) {
            printf("%d (%d) -> ", node->id, node->weight);
            node = node->next;
        }
        printf("\n");
    }
}

// Define a function to implement Dijkstra's algorithm
void dijkstra(GraphNode** graph, int numNodes, int source) {
    int* distances = (int*) malloc(sizeof(int) * numNodes);
    int* previous = (int*) malloc(sizeof(int) * numNodes);

    // Initialize distances and previous nodes
    for (int i = 0; i < numNodes; i++) {
        if (i == source) {
            distances[i] = 0;
        } else {
            distances[i] = INT_MAX;
        }
        previous[i] = -1;
    }

    // Relax edges repeatedly
    for (int i = 0; i < numNodes; i++) {
        GraphNode* node = (*graph)[i];
        while (node != NULL) {
            int dest = node->id;
            if (distances[dest] > distances[i] + node->weight) {
                distances[dest] = distances[i] + node->weight;
                previous[dest] = i;
            }
            node = node->next;
        }
    }

    // Print the shortest distances
    printf("Shortest distances from Node %d:\n", source);
    for (int i = 0; i < numNodes; i++) {
        printf("%d: %d\n", i, distances[i]);
    }

    // Print the previous nodes in the shortest path
    printf("Previous nodes in shortest path:\n");
    for (int i = 0; i < numNodes; i++) {
        if (previous[i] == -1) {
            printf("%d: No previous node\n", i);
        } else {
            printf("%d: %d\n", i, previous[i]);
        }
    }

    // Free memory
    free(distances);
    free(previous);
}

int main() {
    int numNodes = 6;
    GraphNode** graph = (GraphNode**) malloc(sizeof(GraphNode*) * numNodes);

    for (int i = 0; i < numNodes; i++) {
        (*graph)[i] = NULL;
    }

    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 3);
    addEdge(graph, 1, 2, 2);
    addEdge(graph, 1, 3, 5);
    addEdge(graph, 2, 3, 1);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 3, 5, 6);
    addEdge(graph, 4, 5, 7);

    printGraph(graph, numNodes);

    dijkstra(graph, numNodes, 0);

    free(*graph);
    return 0;
}