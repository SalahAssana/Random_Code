#include <stdio.h>
#include <stdlib.h>

// Define the maximum size of the grid
#define MAX_SIZE 100

// Define the state of a cell (alive or dead)
typedef enum { DEAD, ALIVE } CellState;

// Define the structure for a cell
typedef struct {
    int x;
    int y;
    CellState state;
} Cell;

// Function to initialize the grid with random cells
void initGrid(Cell*** grid, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (rand() % 2 == 0) {
                grid[i][j]->state = ALIVE;
            } else {
                grid[i][j]->state = DEAD;
            }
        }
    }
}

// Function to count the number of alive neighbors for a cell
int countAliveNeighbors(Cell*** grid, int x, int y, int size) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if ((i == 0 && j == 0) || x + i < 0 || y + j < 0 || x + i >= size || y + j >= size) continue;
            if (grid[x + i][y + j]->state == ALIVE) count++;
        }
    }
    return count;
}

// Function to update the state of a cell
void updateCell(Cell*** grid, int x, int y, int size) {
    Cell* cell = grid[x][y];
    int aliveNeighbors = countAliveNeighbors(grid, x, y, size);
    
    if (cell->state == ALIVE && (aliveNeighbors < 2 || aliveNeighbors > 3)) {
        cell->state = DEAD;
    } else if (cell->state == DEAD && aliveNeighbors == 3) {
        cell->state = ALIVE;
    }
}

// Function to update the entire grid
void updateGrid(Cell*** grid, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            updateCell(grid, i, j, size);
        }
    }
}

// Function to print the grid
void printGrid(Cell*** grid, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (grid[i][j]->state == ALIVE) printf("* ");
            else printf(". ");
        }
        printf("\n");
    }
}

// Main function
int main() {
    // Initialize the grid with random cells
    Cell*** grid = (Cell***)malloc(MAX_SIZE * sizeof(Cell*));
    for (int i = 0; i < MAX_SIZE; i++) {
        grid[i] = (Cell*)malloc(MAX_SIZE * sizeof(Cell));
    }
    
    initGrid(grid, MAX_SIZE);
    
    // Update the grid and print it
    int generation = 0;
    while (1) {
        updateGrid(grid, MAX_SIZE);
        printf("Generation %d:\n", generation++);
        printGrid(grid, MAX_SIZE);
        
        // Wait for a short time before updating again
        sleep(1);
    }
    
    return 0;
}