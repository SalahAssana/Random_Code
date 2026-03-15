#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define the graph structure
typedef struct {
    int id;
    int weight;
    struct edge* next;
} edge;

typedef struct {
    int id;
    edge* head;
} node;

// Function to create a new edge
edge* create_edge(int id, int weight) {
    edge* new_edge = (edge*)malloc(sizeof(edge));
    new_edge->id = id;
    new_edge->weight = weight;
    new_edge->next = NULL;
    return new_edge;
}

// Function to create a new node
node* create_node(int id) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->id = id;
    new_node->head = NULL;
    return new_node;
}

// Function to insert an edge into the graph
void insert_edge(node* node1, int node2_id, int weight) {
    edge* new_edge = create_edge(node2_id, weight);
    if (node1->head == NULL) {
        node1->head = new_edge;
    } else {
        edge* temp = node1->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_edge;
    }
}

// Function to find the shortest path using Dijkstra's algorithm
void dijkstra(node* start, int end_id, int** distance_matrix, int** prev_matrix) {
    int num_nodes = 0;
    edge* temp = start->head;
    while (temp != NULL) {
        num_nodes++;
        temp = temp->next;
    }

    // Initialize the distance matrix with infinity
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            if (i == j) {
                distance_matrix[i][j] = 0;
            } else {
                distance_matrix[i][j] = INT_MAX;
            }
        }
    }

    // Initialize the previous node matrix with -1
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            prev_matrix[i][j] = -1;
        }
    }

    // Set the distance to the start node as 0
    for (int i = 0; i < num_nodes; i++) {
        if (start->id == i) {
            distance_matrix[0][i] = 0;
        } else {
            distance_matrix[0][i] = INT_MAX;
        }
    }

    // Run Dijkstra's algorithm
    for (int i = 1; i < num_nodes; i++) {
        int min_distance = INT_MAX, min_node = -1;
        for (int j = 0; j < num_nodes; j++) {
            if (distance_matrix[i-1][j] != INT_MAX && distance_matrix[i-1][j] + temp->weight < min_distance) {
                min_distance = distance_matrix[i-1][j] + temp->weight;
                min_node = j;
            }
        }

        // Update the distance and previous node matrices
        for (int k = 0; k < num_nodes; k++) {
            if (distance_matrix[i-1][k] != INT_MAX && distance_matrix[i-1][k] + temp->weight < distance_matrix[i][k]) {
                distance_matrix[i][k] = distance_matrix[i-1][k] + temp->weight;
                prev_matrix[i][k] = min_node;
            }
        }

        // Update the current node
        temp = start->head;
        while (temp != NULL) {
            if (temp->id == min_node) {
                break;
            }
            temp = temp->next;
        }
    }

    // Find the shortest path from the start node to the end node
    int curr_node = end_id, prev_node = -1;
    int path_length = 0;
    while (curr_node != start->id) {
        if (prev_matrix[0][curr_node] == -1) {
            printf("No path found\n");
            return;
        }
        path_length++;
        curr_node = prev_matrix[0][curr_node];
    }

    // Print the shortest path
    printf("Shortest path: ");
    for (int i = 0; i <= path_length; i++) {
        if (i == path_length) {
            printf("%d\n", start->id);
        } else {
            printf("%d -> ", prev_matrix[0][curr_node]);
            curr_node = prev_matrix[0][curr_node];
        }
    }
}

int main() {
    // Create the graph nodes
    node* node1 = create_node(0);
    node* node2 = create_node(1);
    node* node3 = create_node(2);

    // Insert edges into the graph
    insert_edge(node1, 1, 4);
    insert_edge(node1, 2, 8);
    insert_edge(node2, 1, 10);
    insert_edge(node2, 0, 5);
    insert_edge(node3, 2, 3);

    // Create the distance and previous node matrices
    int** distance_matrix = (int**)malloc(1 * sizeof(int*));
    for (int i = 0; i < 1; i++) {
        distance_matrix[i] = (int*)malloc(4 * sizeof(int));
    }
    int** prev_matrix = (int**)malloc(1 * sizeof(int*));
    for (int i = 0; i < 1; i++) {
        prev_matrix[i] = (int*)malloc(4 * sizeof(int));
    }

    // Run Dijkstra's algorithm
    dijkstra(node1, 2, distance_matrix, prev_matrix);

    return 0;
}