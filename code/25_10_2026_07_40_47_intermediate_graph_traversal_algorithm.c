#include <stdio.h>
#include <stdlib.h>

// Define the graph structure
typedef struct {
    int vertices;
    int **adjacencyList;
} Graph;

// Function to create a new graph with given number of vertices
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacencyList = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adjacencyList[i] = (int*)malloc(sizeof(int));
    }
    return graph;
}

// Function to add edge between two vertices
void addEdge(Graph* graph, int source, int destination) {
    if (source >= graph->vertices || destination >= graph->vertices) {
        printf("Invalid vertex: %d or %d\n", source, destination);
        return;
    }
    graph->adjacencyList[source][0] = destination;
}

// Function to perform BFS traversal
void BFS(Graph* graph, int startVertex) {
    int visited[graph->vertices];
    for (int i = 0; i < graph->vertices; i++) {
        visited[i] = 0;
    }
    printf("BFS Traversal: ");
    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            printf("%d ", startVertex);
            visited[startVertex] = 1;
            for (int j = 0; j < graph->vertices; j++) {
                if (graph->adjacencyList[i][0] == j && !visited[j]) {
                    printf("%d ", j);
                    visited[j] = 1;
                }
            }
            printf("\n");
        }
    }
}

// Function to perform DFS traversal
void DFS(Graph* graph, int startVertex) {
    int visited[graph->vertices];
    for (int i = 0; i < graph->vertices; i++) {
        visited[i] = 0;
    }
    printf("DFS Traversal: ");
    DFSUtil(graph, startVertex, visited);
}

// Helper function for DFS traversal
void DFSUtil(Graph* graph, int vertex, int visited[]) {
    if (visited[vertex]) return;
    printf("%d ", vertex);
    visited[vertex] = 1;
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjacencyList[vertex][0] == i && !visited[i]) {
            DFSUtil(graph, i, visited);
        }
    }
}

// Main function
int main() {
    // Create a new graph with 5 vertices
    Graph* graph = createGraph(5);

    // Add edges to the graph
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);

    // Perform BFS traversal starting from vertex 0
    printf("BFS Traversal: ");
    BFS(graph, 0);
    printf("\n");

    // Perform DFS traversal starting from vertex 0
    printf("DFS Traversal: ");
    DFS(graph, 0);
    printf("\n");

    return 0;
}