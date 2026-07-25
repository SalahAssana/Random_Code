#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the graph
typedef struct {
    int x, y;
    int cost;
} Node;

// Function to calculate the heuristic value for a given node
int heuristic(Node *node, Node *goal) {
    return abs(node->x - goal->x) + abs(node->y - goal->y);
}

// Function to perform A* algorithm
Node *aStar(Node *start, Node *goal, int **maze) {
    // Create a priority queue for nodes
    int queueSize = 0;
    Node **queue = (Node **)malloc(sizeof(Node *) * 10000);
    int front = -1;

    // Create a dictionary to store the parent of each node
    Node *parents[10000];
    parents[0] = NULL;

    // Create a priority queue for nodes
    Node *current;
    Node *temp;
    int tempCost, newCost;

    // Initialize the start node with its cost and parent
    current = (Node *)malloc(sizeof(Node));
    current->x = start->x;
    current->y = start->y;
    current->cost = 0;
    parents[queueSize] = current;
    queue[queueSize++] = current;

    while (front < queueSize - 1) {
        front++;
        temp = queue[front];
        if (temp->x == goal->x && temp->y == goal->y) {
            // Reconstruct the path from start to goal
            Node *path[10000];
            int pathLength = 0;
            while (temp != NULL) {
                path[pathLength] = temp;
                temp = parents[temp->cost - 1];
                pathLength++;
            }

            // Return the reconstructed path
            for (int i = pathLength - 1; i >= 0; i--) {
                printf("Node (%d, %d)\n", path[i]->x, path[i]->y);
            }
            return path[pathLength - 1];
        }

        // Calculate the cost and heuristic value of each neighbor
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if ((i == 0 || j == 0) && maze[temp->x + i][temp->y + j] != 1)
                    continue;
                tempCost = temp->cost + 1;
                newCost = tempCost + heuristic(&((Node *)malloc(sizeof(Node))), goal);

                // Check if the neighbor is already in the queue
                for (int k = 0; k < front; k++) {
                    if (queue[k]->x == temp->x + i && queue[k]->y == temp->y + j) {
                        free(temp);
                        return aStar(start, goal, maze);
                    }
                }

                // Add the neighbor to the priority queue
                current = (Node *)malloc(sizeof(Node));
                current->x = temp->x + i;
                current->y = temp->y + j;
                current->cost = newCost;
                parents[queueSize] = temp;
                queue[queueSize++] = current;
            }
        }

        // Free the current node
        free(temp);
    }

    printf("No path found\n");
    return NULL;
}

int main() {
    // Define the maze
    int maze[10][10] = {
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    // Define the start and goal nodes
    Node start;
    start.x = 0;
    start.y = 0;

    Node goal;
    goal.x = 9;
    goal.y = 9;

    // Find the shortest path using A* algorithm
    aStar(&start, &goal, maze);

    return 0;
}