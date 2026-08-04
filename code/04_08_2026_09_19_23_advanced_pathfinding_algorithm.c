#include <stdio.h>
#include <stdlib.h>

// Define the structure for nodes in the graph
typedef struct Node {
    int id;
    int weight;
    struct Node* next;
} Node;

// Define the structure for edges in the graph
typedef struct Edge {
    int source;
    int destination;
    int weight;
} Edge;

// Define the structure for the graph itself
typedef struct Graph {
    Node** nodes;
    Edge** edges;
    int numNodes;
    int numEdges;
} Graph;

// Function to create a new node
Node* createNode(int id) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    newNode->weight = 0;
    newNode->next = NULL;
    return newNode;
}

// Function to add an edge between two nodes
void addEdge(Graph* graph, int source, int destination, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->source = source;
    newEdge->destination = destination;
    newEdge->weight = weight;

    // Add the edge to the list of edges
    if(graph->numEdges == 0) {
        graph->edges = (Edge**)malloc(sizeof(Edge*));
        graph->edges[0] = newEdge;
        graph->numEdges = 1;
    } else {
        Edge** temp = (Edge**)malloc((graph->numEdges + 1)*sizeof(Edge*));
        for(int i = 0; i < graph->numEdges; i++) {
            temp[i] = graph->edges[i];
        }
        temp[graph->numEdges] = newEdge;
        free(graph->edges);
        graph->edges = temp;
        graph->numEdges++;
    }
}

// Function to create a new graph
Graph* createGraph(int numNodes) {
    Graph* newGraph = (Graph*)malloc(sizeof(Graph));
    newGraph->nodes = (Node**)malloc(numNodes*sizeof(Node*));
    newGraph->edges = NULL;
    newGraph->numNodes = numNodes;
    newGraph->numEdges = 0;

    for(int i = 0; i < numNodes; i++) {
        newGraph->nodes[i] = createNode(i);
    }

    return newGraph;
}

// Function to free the memory used by a graph
void freeGraph(Graph* graph) {
    for(int i = 0; i < graph->numNodes; i++) {
        Node* node = graph->nodes[i];
        while(node != NULL) {
            Node* temp = node;
            node = node->next;
            free(temp);
        }
    }

    if(graph->edges != NULL) {
        for(int i = 0; i < graph->numEdges; i++) {
            Edge* edge = graph->edges[i];
            free(edge);
        }
        free(graph->edges);
    }

    free(graph->nodes);
    free(graph);
}

// Function to find the shortest path between two nodes using Dijkstra's algorithm
void dijkstra(Graph* graph, int startNode, int endNode) {
    // Create a table to hold the distance from the start node to each other node
    int* distances = (int*)malloc(graph->numNodes*sizeof(int));
    for(int i = 0; i < graph->numNodes; i++) {
        distances[i] = INT_MAX;
    }

    // The distance from the start node to itself is 0
    distances[startNode] = 0;

    // Create a table to hold the previous node in the shortest path
    int* previous = (int*)malloc(graph->numNodes*sizeof(int));
    for(int i = 0; i < graph->numNodes; i++) {
        previous[i] = -1;
    }

    // Create a priority queue to hold the nodes that are being processed
    Node* nodeQueue = NULL;
    for(int i = 0; i < graph->numNodes; i++) {
        if(i != startNode) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->id = i;
            newNode->weight = distances[i];
            newNode->next = nodeQueue;
            nodeQueue = newNode;
        }
    }

    // Process the nodes in the priority queue
    while(nodeQueue != NULL) {
        Node* currentNode = nodeQueue;
        nodeQueue = nodeQueue->next;

        // For each edge leaving the current node
        for(int i = 0; i < graph->numEdges; i++) {
            Edge* edge = graph->edges[i];
            if(edge->source == currentNode->id) {
                int neighborId = edge->destination;
                int weight = edge->weight;

                // If the distance to the current node plus the weight of the edge is less than the known distance
                if(distances[currentNode->id] + weight < distances[neighborId]) {
                    // Update the distance and previous node for the neighbor
                    distances[neighborId] = distances[currentNode->id] + weight;
                    previous[neighborId] = currentNode->id;

                    // Add the neighbor to the priority queue if it's not already being processed
                    Node* newNode = (Node*)malloc(sizeof(Node));
                    newNode->id = neighborId;
                    newNode->weight = distances[neighborId];
                    newNode->next = nodeQueue;
                    nodeQueue = newNode;
                }
            }
        }

        // Free the current node
        free(currentNode);
    }

    // Print the shortest path from the start node to the end node
    int currentNodeId = endNode;
    while(currentNodeId != -1) {
        printf("%d ", currentNodeId);
        currentNodeId = previous[currentNodeId];
    }
    printf("\n");

    // Free the distance and previous tables
    free(distances);
    free(previous);
}

int main() {
    // Create a new graph with 5 nodes
    Graph* graph = createGraph(5);

    // Add edges to the graph
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 3);
    addEdge(graph, 1, 2, 2);
    addEdge(graph, 1, 3, 10);
    addEdge(graph, 2, 1, 14);
    addEdge(graph, 2, 3, 5);
    addEdge(graph, 3, 4, 7);
    addEdge(graph, 4, 3, 9);

    // Find the shortest path from node 0 to node 4
    dijkstra(graph, 0, 4);

    // Free the memory used by the graph
    freeGraph(graph);

    return 0;
}