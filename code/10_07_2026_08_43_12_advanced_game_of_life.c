#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the possible states of a cell (dead or alive)
typedef enum { DEAD, ALIVE } CellState;

// Define the structure to represent a cell in the grid
typedef struct {
    CellState state;
    int x; // coordinates of the cell
    int y;
} Cell;

// Function to print the grid
void printGrid(Cell** grid, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (grid[i][j].state == ALIVE)
                printf("* ");
            else
                printf(". ");
        }
        printf("\n");
    }
}

// Function to count the number of alive neighbors for a given cell
int countAliveNeighbors(Cell** grid, int x, int y, int width, int height) {
    int count = 0;
    // Check all eight directions (up, down, left, right, and diagonals)
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) // ignore the current cell
                continue;
            int newX = x + i;
            int newY = y + j;
            if (newX >= 0 && newX < width && newY >= 0 && newY < height) { // check if coordinates are within bounds
                if (grid[newY][newX].state == ALIVE)
                    count++;
            }
        }
    }
    return count;
}

// Function to apply the Game of Life rules to update a cell's state
void updateCellState(Cell** grid, int x, int y, int width, int height) {
    int aliveNeighbors = countAliveNeighbors(grid, x, y, width, height);
    if (grid[y][x].state == ALIVE) { // cell is currently alive
        if (aliveNeighbors < 2 || aliveNeighbors > 3)
            grid[y][x].state = DEAD; // underpopulation or overpopulation
    } else { // cell is currently dead
        if (aliveNeighbors == 3)
            grid[y][x].state = ALIVE; // birth
    }
}

// Function to update the entire grid based on the Game of Life rules
void updateGrid(Cell** grid, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            updateCellState(grid, j, i, width, height);
        }
    }
}

// Main function to simulate the Game of Life
int main() {
    srand(time(NULL)); // seed random number generator

    int width = 20;
    int height = 10;

    Cell** grid = (Cell**)malloc(height * sizeof(Cell*));
    for (int i = 0; i < height; i++) {
        grid[i] = (Cell*)malloc(width * sizeof(Cell));
    }

    // Initialize the grid with random values
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (rand() % 2 == 1) // random value between 0 and 1, so roughly half are alive
                grid[i][j].state = ALIVE;
            else
                grid[i][j].state = DEAD;
            grid[i][j].x = j;
            grid[i][j].y = i;
        }
    }

    int generation = 0;

    while (1) {
        printf("Generation %d:\n", generation);
        printGrid(grid, width, height);
        updateGrid(grid, width, height);
        generation++;
    }

    for (int i = 0; i < height; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}