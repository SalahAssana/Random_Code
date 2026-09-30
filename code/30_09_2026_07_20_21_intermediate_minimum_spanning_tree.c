#include <stdio.h>
#include <stdlib.h>

// Define a structure for an edge in the graph
typedef struct {
    int u;
    int v;
    int weight;
} Edge;

// Define a structure for a vertex in the graph
typedef struct {
    int id;
    int visited;
} Vertex;

// Function to compare two edges and return 1 if e1 is smaller, -1 otherwise
int edgeCompare(const void* e1, const void* e2) {
    Edge *edge1 = (Edge *)e1;
    Edge *edge2 = (Edge *)e2;
    if (edge1->weight < edge2->weight)
        return -1;
    else if (edge1->weight > edge2->weight)
        return 1;
    else
        return 0;
}

// Function to find the parent of a vertex in the disjoint set
int findParent(int parent[], int vertex) {
    if (parent[vertex] == vertex)
        return vertex;
    else
        return findParent(parent, parent[vertex]);
}

// Function to union two vertices in the disjoint set
void unionVertices(int parent[], int vertex1, int vertex2) {
    int root1 = findParent(parent, vertex1);
    int root2 = findParent(parent, vertex2);
    if (root1 != root2)
        parent[root2] = root1;
}

// Function to generate the minimum spanning tree using Kruskal's algorithm
void kruskalMST(int numVertices, Edge edges[], int numEdges) {
    // Create an array to store the parent of each vertex in the disjoint set
    int parent[numVertices];
    for (int i = 0; i < numVertices; i++)
        parent[i] = i;

    // Sort the edges based on their weights
    qsort(edges, numEdges, sizeof(Edge), edgeCompare);

    // Initialize an array to store the minimum spanning tree edges
    Edge mstEdges[100]; // Assuming a maximum of 100 edges in the MST

    int numMSTEdges = 0;
    for (int i = 0; i < numEdges; i++) {
        int vertex1 = edges[i].u;
        int vertex2 = edges[i].v;

        if (findParent(parent, vertex1) != findParent(parent, vertex2)) {
            mstEdges[numMSTEdges] = edges[i];
            unionVertices(parent, vertex1, vertex2);
            numMSTEdges++;
        }
    }

    // Print the minimum spanning tree
    printf("Minimum Spanning Tree:\n");
    for (int i = 0; i < numMSTEdges; i++) {
        printf("(%d,%d) weight:%d\n", mstEdges[i].u, mstEdges[i].v, mstEdges[i].weight);
    }
}

// Function to generate synthetic data for testing
void generateTestData(int numVertices, Edge edges[], int numEdges) {
    // Generate random vertices and edges
    for (int i = 0; i < numVertices; i++) {
        edges[i].u = i;
        edges[i].v = (i + 1) % numVertices;
        edges[i].weight = rand() % 100;
    }
}

int main() {
    // Define the number of vertices and edges in the graph
    int numVertices = 5;
    int numEdges = 10;

    // Generate synthetic data for testing
    Edge edges[numEdges];
    generateTestData(numVertices, edges, numEdges);

    // Run Kruskal's algorithm to find the minimum spanning tree
    kruskalMST(numVertices, edges, numEdges);

    return 0;
}