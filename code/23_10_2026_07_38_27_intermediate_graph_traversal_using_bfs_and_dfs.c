#include <stdio.h>
#include <stdlib.h>

// Structure to represent an adjacency list node
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

// Structure to represent a graph node
typedef struct GraphNode {
    int data;
    AdjListNode* head;
} GraphNode;

// Function to create a new adjacency list node
AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to print BFS traversal of the graph
void bfsTraversal(GraphNode* graph, int start) {
    int visited[graph->data + 1];
    for (int i = 0; i <= graph->data; i++) {
        visited[i] = 0;
    }
    int queue[graph->data + 1], front = 0, rear = 0;
    printf("BFS Traversal: ");
    while (front <= rear) {
        int temp = queue[front++];
        if (!visited[temp]) {
            printf("%d ", temp);
            visited[temp] = 1;
            AdjListNode* p = graph->head + temp;
            while (p) {
                if (!visited[p->dest]) {
                    queue[++rear] = p->dest;
                }
                p = p->next;
            }
        }
    }
    printf("\n");
}

// Function to print DFS traversal of the graph
void dfsTraversal(GraphNode* graph, int start, int visited[]) {
    printf("%d ", start);
    visited[start] = 1;
    AdjListNode* p = graph->head + start;
    while (p) {
        if (!visited[p->dest]) {
            dfsTraversal(graph, p->dest, visited);
        }
        p = p->next;
    }
}

// Function to create a new graph node
GraphNode* newGraphNode(int data) {
    GraphNode* newNode = (GraphNode*)malloc(sizeof(GraphNode));
    newNode->data = data;
    newNode->head = NULL;
    return newNode;
}

int main() {
    int graphData = 5; // Number of vertices in the graph

    // Create a graph with 5 vertices
    GraphNode* graph = newGraphNode(graphData);
    for (int i = 0; i < graphData; i++) {
        graph->head[i] = NULL;
    }

    // Add edges to the graph
    AdjListNode* p1 = newAdjListNode(1);
    p1->next = newAdjListNode(2);
    graph->head[0] = p1;

    AdjListNode* p2 = newAdjListNode(3);
    p2->next = newAdjListNode(4);
    graph->head[1] = p2;
    graph->head[2]->next = newAdjListNode(4);
    graph->head[3]->next = newAdjListNode(0);

    // Perform BFS and DFS traversals
    int startVertex = 0; // Starting vertex for traversal
    int visited[graphData + 1];
    for (int i = 0; i <= graphData; i++) {
        visited[i] = 0;
    }
    bfsTraversal(graph, startVertex);
    dfsTraversal(graph, startVertex, visited);

    return 0;
}