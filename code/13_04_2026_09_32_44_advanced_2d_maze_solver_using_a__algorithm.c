#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the possible directions in the maze (up, down, left, right)
enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// Define a struct to represent a node in the maze
typedef struct {
    int x; // x-coordinate of the node
    int y; // y-coordinate of the node
    enum direction cameFrom; // direction from which the node was reached
} Node;

// Function to generate a random 2D maze
void generateMaze(int **maze, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ((rand() % 2) == 0) {
                // Create a wall
                maze[i][j] = 1;
            } else {
                // Create an open space
                maze[i][j] = 0;
            }
        }
    }
}

// Function to check if two nodes are adjacent (i.e., they share an edge)
int isAdjacent(Node node1, Node node2) {
    if ((node1.x == node2.x && abs(node1.y - node2.y) == 1) ||
        (node1.y == node2.y && abs(node1.x - node2.x) == 1)) {
        return 1;
    } else {
        return 0;
    }
}

// Function to calculate the Manhattan distance between two nodes
int manhattanDistance(Node node1, Node node2) {
    return abs(node1.x - node2.x) + abs(node1.y - node2.y);
}

// Function to perform A* search
void aStarSearch(int **maze, int startX, int startY, int endX, int endY) {
    // Create a priority queue to hold the nodes to be processed
    NodeQueue *queue = (NodeQueue *)malloc(sizeof(NodeQueue));
    Node head = {startX, startY, UP};
    enqueue(queue, &head);

    while (!isEmpty(queue)) {
        Node node = dequeue(queue);
        if (node.x == endX && node.y == endY) {
            // Path found! Reconstruct the path
            printf("Path found!\n");
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX, newY;
            switch (i) {
                case UP:
                    newX = node.x;
                    newY = node.y - 1;
                    break;
                case DOWN:
                    newX = node.x;
                    newY = node.y + 1;
                    break;
                case LEFT:
                    newX = node.x - 1;
                    newY = node.y;
                    break;
                case RIGHT:
                    newX = node.x + 1;
                    newY = node.y;
                    break;
            }

            if (isAdjacent(node, (Node){newX, newY})) {
                // Check if the new node is within the maze boundaries
                if (newX >= 0 && newX < 10 && newY >= 0 && newY < 10) {
                    int cost = manhattanDistance((Node){endX, endY}, (Node){newX, newY});
                    Node newNode = {newX, newY, i};
                    enqueue(queue, &newNode);
                }
            }
        }
    }

    printf("No path found.\n");
}

// Function to check if the priority queue is empty
int isEmpty(NodeQueue *queue) {
    return queue->size == 0;
}

// Function to dequeue an element from the priority queue
Node dequeue(NodeQueue *queue) {
    Node node = queue->head;
    queue->head = (Node *)malloc(sizeof(Node));
    *(queue->head) = *(queue->tail);
    queue->tail = NULL;
    queue->size--;
    return node;
}

// Function to enqueue an element into the priority queue
void enqueue(NodeQueue *queue, Node *node) {
    if (queue->size == 0) {
        queue->head = node;
        queue->tail = node;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }
    queue->size++;
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    int width = 10, height = 10; // Define the dimensions of the maze
    int **maze = (int **)malloc(sizeof(int *) * height);
    for (int i = 0; i < height; i++) {
        maze[i] = (int *)malloc(sizeof(int) * width);
    }

    generateMaze(maze, width, height);

    // Define the start and end points of the path
    int startX = 1;
    int startY = 1;
    int endX = 8;
    int endY = 8;

    aStarSearch(maze, startX, startY, endX, endY);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < height; i++) {
        free(maze[i]);
    }
    free(maze);

    return 0;
}