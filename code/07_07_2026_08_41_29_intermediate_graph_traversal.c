#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INFINITY 1000000

typedef struct {
    int vertex;
    int weight;
} Edge;

typedef struct {
    int visited;
    int distance;
    Edge* edges;
} Vertex;

void BFS(Vertex* vertices, int startVertex) {
    int i, j;
    for (i = 0; i < MAX_VERTICES; i++) {
        vertices[i].visited = 0;
        vertices[i].distance = INFINITY;
    }

    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
    queue[rear++] = startVertex;

    while (front != rear) {
        int currentVertex = queue[front++];
        printf("Visited vertex %d\n", currentVertex);

        for (i = 0; i < MAX_VERTICES; i++) {
            if (vertices[i].visited == 0 && vertices[currentVertex].edges[i].weight != INFINITY) {
                queue[rear++] = i;
                vertices[i].visited = 1;
                vertices[i].distance = vertices[currentVertex].distance + 1;
            }
        }
    }
}

void DFS(Vertex* vertices, int startVertex) {
    int i;

    printf("Visited vertex %d\n", startVertex);

    for (i = 0; i < MAX_VERTICES; i++) {
        if (vertices[i].visited == 0 && vertices[startVertex].edges[i].weight != INFINITY) {
            DFS(vertices, i);
        }
    }
}

int main() {
    Vertex* vertices = (Vertex*)malloc(MAX_VERTICES * sizeof(Vertex));

    for (int i = 0; i < MAX_VERTICES; i++) {
        vertices[i].visited = 0;
        vertices[i].distance = INFINITY;
    }

    // Add edges to the graph
    vertices[0].edges = (Edge*)malloc(MAX_VERTICES * sizeof(Edge));
    vertices[0].edges[1].vertex = 1;
    vertices[0].edges[1].weight = 4;

    vertices[0].edges[2].vertex = 2;
    vertices[0].edges[2].weight = 8;

    // Example graph: Directed Graph with 3 vertices and edges
    vertices[1].edges = (Edge*)malloc(MAX_VERTICES * sizeof(Edge));
    vertices[1].edges[0].vertex = 0;
    vertices[1].edges[0].weight = 4;

    vertices[1].edges[2].vertex = 2;
    vertices[1].edges[2].weight = 8;

    vertices[2].edges = (Edge*)malloc(MAX_VERTICES * sizeof(Edge));
    vertices[2].edges[0].vertex = 0;
    vertices[2].edges[0].weight = 8;

    BFS(vertices, 0);
    DFS(vertices, 0);

    for (int i = 0; i < MAX_VERTICES; i++) {
        free(vertices[i].edges);
    }
    free(vertices);

    return 0;
}