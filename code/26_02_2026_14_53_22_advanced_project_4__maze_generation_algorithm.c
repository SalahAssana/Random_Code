#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure to represent a cell in the maze
typedef struct {
    int x, y;
    int visited;
} Cell;

// Function to generate a random maze using DFS algorithm
void generateMaze(int rows, int cols, Cell cells[]) {
    // Start at a random cell
    int startX = rand() % rows;
    int startY = rand() % cols;
    Cell* startCell = &cells[startX * cols + startY];

    // Mark the starting cell as visited
    startCell->visited = 1;

    // Use DFS to generate the maze
    dfs(&startCell, cells, rows, cols);
}

// Recursive function to perform DFS and carve out paths in the maze
void dfs(Cell** currentCell, Cell* cells[], int rows, int cols) {
    // Get the neighbors of the current cell
    int x = (*currentCell)->x;
    int y = (*currentCell)->y;

    // Check if all neighbors have been visited
    if (allVisited(x, y, cells, rows, cols)) return;

    // Carve out a path to a random unvisited neighbor
    Cell* neighbor = getRandomNeighbor(x, y, cells, rows, cols);
    if (neighbor != NULL) {
        // Mark the current cell as visited
        (*currentCell)->visited = 1;

        // Recursively explore the new path
        dfs(&neighbor, cells, rows, cols);

        // Backtrack to the previous cell
        backtrack(x, y, cells, rows, cols);
    }
}

// Function to check if all neighbors of a cell have been visited
int allVisited(int x, int y, Cell* cells[], int rows, int cols) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int newX = x + i;
            int newY = y + j;

            // Check if the neighbor is within the maze boundaries
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                Cell* neighborCell = &cells[newX * cols + newY];
                if (!neighborCell->visited) return 0;
            }
        }
    }

    // If all neighbors have been visited, return 1
    return 1;
}

// Function to get a random unvisited neighbor of a cell
Cell* getRandomNeighbor(int x, int y, Cell* cells[], int rows, int cols) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int newX = x + i;
            int newY = y + j;

            // Check if the neighbor is within the maze boundaries
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                Cell* neighborCell = &cells[newX * cols + newY];
                if (!neighborCell->visited) return neighborCell;
            }
        }
    }

    // If no unvisited neighbors are found, return NULL
    return NULL;
}

// Function to backtrack from a cell and restore the maze
void backtrack(int x, int y, Cell* cells[], int rows, int cols) {
    // Get the current cell
    Cell* currentCell = &cells[x * cols + y];

    // Mark the current cell as unvisited
    currentCell->visited = 0;

    // Backtrack to a previous cell
    if (x > 0 && cells[(x - 1) * cols + y]->visited == 0) {
        backtrack(x - 1, y, cells, rows, cols);
    } else if (y > 0 && cells[x * cols + y - 1]->visited == 0) {
        backtrack(x, y - 1, cells, rows, cols);
    }
}

int main() {
    srand(time(NULL));

    // Set the dimensions of the maze
    int rows = 10;
    int cols = 20;

    // Create an array to represent the maze
    Cell* cells = (Cell*)malloc(rows * cols * sizeof(Cell));
    for (int i = 0; i < rows * cols; i++) {
        cells[i].x = i / cols;
        cells[i].y = i % cols;
        cells[i].visited = 0;
    }

    // Generate the maze
    generateMaze(rows, cols, cells);

    // Print the generated maze
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (cells[i * cols + j].visited) printf("##");
            else printf("  ");
        }
        printf("\n");
    }

    free(cells);

    return 0;
}