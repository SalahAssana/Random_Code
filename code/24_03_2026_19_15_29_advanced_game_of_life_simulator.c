#include <stdio.h>
#include <stdlib.h>

// Define constants for Game of Life rules
#define LIVE 1
#define DEAD 0
#define NEXT_GEN 2

// Structure to represent a cell in the grid
typedef struct {
    int state; // State of the cell (LIVE or DEAD)
} Cell;

// Function to initialize the grid with random states
void initGrid(Cell** grid, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            // Randomly set cell state to LIVE or DEAD
            if(rand() % 2 == 1) {
                grid[i][j].state = LIVE;
            } else {
                grid[i][j].state = DEAD;
            }
        }
    }
}

// Function to count live neighbors for a given cell
int countLiveNeighbors(Cell** grid, int i, int j, int rows, int cols) {
    int liveNeighbors = 0;
    // Count live neighbors (up, down, left, right, and diagonals)
    for(int x = -1; x <= 1; x++) {
        for(int y = -1; y <= 1; y++) {
            if(x == 0 && y == 0) continue; // Skip the cell itself
            int neighborI = i + x;
            int neighborJ = j + y;
            // Check boundaries and wrap around if necessary
            if(neighborI < 0 || neighborI >= rows || neighborJ < 0 || neighborJ >= cols) {
                continue;
            }
            if(grid[neighborI][neighborJ].state == LIVE) {
                liveNeighbors++;
            }
        }
    }
    return liveNeighbors;
}

// Function to apply Game of Life rules and generate the next generation
void nextGen(Cell** grid, int rows, int cols) {
    Cell** nextGrid = (Cell**)malloc(rows * sizeof(Cell*));
    for(int i = 0; i < rows; i++) {
        nextGrid[i] = (Cell*)malloc(cols * sizeof(Cell));
    }
    
    // Apply rules to each cell
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            int liveNeighbors = countLiveNeighbors(grid, i, j, rows, cols);
            if(grid[i][j].state == LIVE) {
                // Any live cell with fewer than two live neighbors dies, while any live cell with two or three live neighbors lives on to the next generation.
                if(liveNeighbors < 2 || liveNeighbors > 3) {
                    nextGrid[i][j].state = DEAD;
                } else {
                    nextGrid[i][j].state = LIVE;
                }
            } else {
                // Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
                if(liveNeighbors == 3) {
                    nextGrid[i][j].state = LIVE;
                } else {
                    nextGrid[i][j].state = DEAD;
                }
            }
        }
    }
    
    // Update the grid
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            grid[i][j] = nextGrid[i][j];
        }
    }
    
    free(nextGrid);
}

// Function to print the grid as a ASCII art representation
void printGrid(Cell** grid, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(grid[i][j].state == LIVE) {
                printf("* ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

int main() {
    // Initialize random number generator
    srand(time(NULL));
    
    // Define the grid dimensions (change these values to vary the simulation)
    int rows = 20;
    int cols = 40;
    
    Cell** grid = (Cell**)malloc(rows * sizeof(Cell*));
    for(int i = 0; i < rows; i++) {
        grid[i] = (Cell*)malloc(cols * sizeof(Cell));
    }
    
    // Initialize the grid with random states
    initGrid(grid, rows, cols);
    
    int generations = 100;
    
    for(int gen = 1; gen <= generations; gen++) {
        printf("Generation %d:\n", gen);
        printGrid(grid, rows, cols);
        nextGen(grid, rows, cols);
    }
    
    // Free the grid
    for(int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
    
    return 0;
}