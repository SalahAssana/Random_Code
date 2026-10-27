#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the possible directions (up, down, left, right)
enum Direction {UP, DOWN, LEFT, RIGHT};

// Define the maze structure
typedef struct {
    int rows;
    int cols;
    char **grid; // 0: wall, 1: empty cell, 2: start point, 3: end point
} Maze;

// Function to generate a random maze
Maze* generateMaze(int rows, int cols) {
    Maze* maze = (Maze*)malloc(sizeof(Maze));
    maze->rows = rows;
    maze->cols = cols;
    maze->grid = (char**)malloc(rows * sizeof(char*));

    for (int i = 0; i < rows; i++) {
        maze->grid[i] = (char*)malloc(cols * sizeof(char));
    }

    // Initialize the grid with walls
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            maze->grid[i][j] = '0';
        }
    }

    // Set start and end points
    int startX, startY, endX, endY;
    startX = rand() % rows;
    startY = rand() % cols;
    endX = rand() % rows;
    endY = rand() % cols;

    maze->grid[startX][startY] = '2';
    maze->grid[endX][endY] = '3';

    return maze;
}

// Function to print the maze
void printMaze(Maze* maze) {
    for (int i = 0; i < maze->rows; i++) {
        for (int j = 0; j < maze->cols; j++) {
            printf("%c ", maze->grid[i][j]);
        }
        printf("\n");
    }
}

// Function to find the shortest path using A* algorithm
void aStar(Maze* maze, int startX, int startY, int endX, int endY) {
    // Create a priority queue for the nodes to visit
    struct Node {
        int x;
        int y;
        float cost;
        struct Node* parent;
    };

    // Function to compare two nodes in the priority queue
    int compareNodes(struct Node* node1, struct Node* node2) {
        if (node1->cost < node2->cost)
            return -1;
        else if (node1->cost > node2->cost)
            return 1;
        else
            return 0;
    }

    // Function to generate the neighbors of a node
    void generateNeighbors(Maze* maze, struct Node* node, int startX, int startY, int endX, int endY) {
        enum Direction directions[] = {UP, DOWN, LEFT, RIGHT};
        for (int i = 0; i < 4; i++) {
            int newX = node->x;
            int newY = node->y;

            switch (directions[i]) {
                case UP:
                    if (newY > 0 && maze->grid[newX][newY - 1] != '0') {
                        newNode.x = newX;
                        newNode.y = newY - 1;
                        newNode.parent = node;
                        newNode.cost = node->cost + 1.0f;
                    }
                    break;
                case DOWN:
                    if (newY < maze->rows - 1 && maze->grid[newX][newY + 1] != '0') {
                        newNode.x = newX;
                        newNode.y = newY + 1;
                        newNode.parent = node;
                        newNode.cost = node->cost + 1.0f;
                    }
                    break;
                case LEFT:
                    if (newX > 0 && maze->grid[newX - 1][newY] != '0') {
                        newNode.x = newX - 1;
                        newNode.y = newY;
                        newNode.parent = node;
                        newNode.cost = node->cost + 1.0f;
                    }
                    break;
                case RIGHT:
                    if (newX < maze->cols - 1 && maze->grid[newX + 1][newY] != '0') {
                        newNode.x = newX + 1;
                        newY = newY;
                        newNode.parent = node;
                        newNode.cost = node->cost + 1.0f;
                    }
                    break;
            }
        }
    }

    // Function to reconstruct the path from the end node to the start node
    void reconstructPath(Maze* maze, struct Node* endNode) {
        struct Node* currentNode = endNode;
        while (currentNode != NULL) {
            printf(" (%d,%d)", currentNode->x, currentNode->y);
            currentNode = currentNode->parent;
        }
        printf("\n");
    }

    // Main A* algorithm function
    void aStarMain(Maze* maze, int startX, int startY, int endX, int endY) {
        struct Node startNode = {startX, startY, 0.0f, NULL};
        struct Node* endNode = &startNode;

        // Create the priority queue and add the start node
        struct NodeQueue* queue = (struct NodeQueue*)malloc(sizeof(struct NodeQueue));
        queue->head = NULL;
        queue->tail = NULL;

        // Add the start node to the queue
        struct Node newNode = {startX, startY, 0.0f, &startNode};
        queue->head = &newNode;
        queue->tail = &newNode;

        // Initialize the shortest distance and path
        float shortestDistance = INFINITY;
        struct Node* shortestPath = NULL;

        while (queue->head != NULL) {
            // Dequeue the node with the shortest distance
            struct Node* currentNode = queue->head;
            queue->head = queue->head->next;
            if (currentNode == endNode)
                break; // We've reached the end node, stop searching

            // Generate neighbors for the current node
            generateNeighbors(maze, currentNode, startX, startY, endX, endY);

            // Update the shortest distance and path if necessary
            if (currentNode->cost < shortestDistance) {
                shortestDistance = currentNode->cost;
                shortestPath = currentNode;
            }
        }

        // Reconstruct the path from the end node to the start node
        reconstructPath(maze, shortestPath);
    }

int main() {
    srand(time(NULL));

    Maze* maze = generateMaze(10, 10);

    printf("Initial Maze:\n");
    printMaze(maze);

    aStarMain(maze, 0, 0, 9, 9);

    return 0;
}