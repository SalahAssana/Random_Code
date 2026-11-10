#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000
#define INF 9999

typedef struct {
    int x, y;
} Point;

typedef struct {
    int x, y, val;
} Cell;

// Function to find the shortest path using Dijkstra's algorithm
void dijkstra(int **graph, int start, int end, int **path) {
    int n = 5; // Number of cells
    int visited[n]; 
    for (int i = 0; i < n; ++i)
        visited[i] = 0;

    int dist[n]; 
    for (int i = 0; i < n; ++i) {
        dist[i] = INF;
    }
    dist[start] = 0;

    Cell queue[n]; 
    int front = -1, rear = 0;

    // Create a priority queue
    void enqueue(int u) {
        if (front == -1)
            front = rear = 0;
        else if (rear == MAX_SIZE - 1)
            printf("Queue is full!\n");
        else {
            queue[++rear] = (Cell){u, u, dist[u]};
        }
    }

    void dequeue() {
        Cell temp = queue[front++];
        if (front > rear) 
            front = rear = 0;
    }

    // Function to extract minimum distance value from the priority queue
    int getMinDist() {
        int min_dist = INF, u;
        for (int i = 0; i <= rear; ++i) {
            if (queue[i].val < min_dist) {
                min_dist = queue[i].val;
                u = queue[i].x;
            }
        }
        dequeue();
        return u;
    }

    // Function to update the distance value of a cell
    void relax(int v, int w, int weight) {
        if (dist[v] + weight < dist[w]) {
            dist[w] = dist[v] + weight;
        }
    }

    while (1) {
        int u = getMinDist();
        visited[u] = 1;

        for (int i = 0; i < n; ++i) {
            if (!visited[i] && graph[u][i] != 0) {
                relax(u, i, graph[u][i]);
            }
        }

        if (u == end)
            break;
    }

    // Function to print the shortest path
    void printPath(int **path, int start, int end) {
        printf("Shortest Path: %d ->", start);
        for (int i = 0; i < n; ++i) {
            if (path[start][i] == 1)
                printf("%d ", i);
        }
        printf("\n");
    }

    printPath(path, start, end);
}

// Function to create the graph
void createGraph(int **graph, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = rand() % 2; 
        }
    }
}

// Main function
int main() {
    srand(time(0));

    int n = 5; // Number of cells

    int **graph = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i)
        graph[i] = (int *)malloc(n * sizeof(int));

    createGraph(graph, n);

    int start = rand() % n;
    int end = rand() % n;

    int **path = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i)
        path[i] = (int *)malloc(n * sizeof(int));

    dijkstra(graph, start, end, path);

    // Free memory
    for (int i = 0; i < n; ++i) {
        free(graph[i]);
        free(path[i]);
    }
    free(graph);
    free(path);

    return 0;
}