#include <stdio.h>
#include <stdlib.h>

// Define the structure for a cell in the maze
typedef struct {
    int x, y; // coordinates of the cell
    int visited; // 0: unvisited, 1: visited
} Cell;

// Function to generate the maze using depth-first search and recursion
void generateMaze(Cell* maze, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Mark the current cell as unvisited
            maze[i * cols + j].visited = 0;
        }
    }

    // Choose a random cell to start the depth-first search from
    int startX = rand() % rows;
    int startY = rand() % cols;

    Cell* currentCell = &maze[startX * cols + startY];

    if (currentCell->visited == 1) {
        return; // The maze is already generated, so exit
    }

    // Recursively generate the maze
    generateMazeRecursively(maze, rows, cols, startX, startY);
}

// Recursive function to generate the maze using depth-first search
void generateMazeRecursively(Cell* maze, int rows, int cols, int x, int y) {
    Cell* currentCell = &maze[x * cols + y];

    // Mark the current cell as visited
    currentCell->visited = 1;

    // Randomly choose a direction to move (up, down, left, right)
    int direction = rand() % 4;
    switch (direction) {
        case 0: // Up
            if (x > 0 && maze[(x - 1) * cols + y].visited == 0) {
                // Carve a path to the top cell
                maze[(x - 1) * cols + y].visited = 1;
                generateMazeRecursively(maze, rows, cols, x - 1, y);
            }
            break;
        case 1: // Down
            if (x < rows - 1 && maze[(x + 1) * cols + y].visited == 0) {
                // Carve a path to the bottom cell
                maze[(x + 1) * cols + y].visited = 1;
                generateMazeRecursively(maze, rows, cols, x + 1, y);
            }
            break;
        case 2: // Left
            if (y > 0 && maze[x * cols + y - 1].visited == 0) {
                // Carve a path to the left cell
                maze[x * cols + y - 1].visited = 1;
                generateMazeRecursively(maze, rows, cols, x, y - 1);
            }
            break;
        case 3: // Right
            if (y < cols - 1 && maze[x * cols + y + 1].visited == 0) {
                // Carve a path to the right cell
                maze[x * cols + y + 1].visited = 1;
                generateMazeRecursively(maze, rows, cols, x, y + 1);
            }
            break;
    }
}

// Function to print the generated maze
void printMaze(Cell* maze, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i * cols + j].visited == 1) {
                printf(" #"); // Print a wall
            } else {
                printf("   "); // Print an open space
            }
        }
        printf("\n");
    }
}

int main() {
    // Set the size of the maze
    int rows = 20;
    int cols = 20;

    // Allocate memory for the maze cells
    Cell* maze = (Cell*)malloc(rows * cols * sizeof(Cell));

    // Generate the maze
    generateMaze(maze, rows, cols);

    // Print the generated maze
    printMaze(maze, rows, cols);

    // Free the allocated memory
    free(maze);

    return 0;
}