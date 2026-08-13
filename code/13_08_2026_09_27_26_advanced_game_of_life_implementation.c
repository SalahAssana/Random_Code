#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the structure for a cell in the game of life
typedef struct {
    int isAlive;
    int neighbors[8]; // up, down, left, right, and all 4 diagonals
} Cell;

// Function to count the number of alive neighbors for a given cell
int countNeighbors(Cell *cell) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (cell->neighbors[i] == 1) {
            count++;
        }
    }
    return count;
}

// Function to apply the rules of the game of life
void applyRules(Cell *cells, int width, int height, Cell *newCells) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Cell *cell = &cells[i * width + j];
            int neighborsAlive = countNeighbors(cell);
            if (cell->isAlive) {
                // Any live cell with fewer than two alive neighbors dies, as if by underpopulation
                if (neighborsAlive < 2) {
                    newCells[i * width + j].isAlive = 0;
                }
                // Any live cell with two or three alive neighbors lives on to the next generation
                else if (neighborsAlive <= 3) {
                    newCells[i * width + j].isAlive = 1;
                }
                // Any live cell with more than three alive neighbors dies, as if by overpopulation
                else {
                    newCells[i * width + j].isAlive = 0;
                }
            } else {
                // Any dead cell with exactly three alive neighbors becomes a live cell, as if by reproduction
                if (neighborsAlive == 3) {
                    newCells[i * width + j].isAlive = 1;
                } else {
                    newCells[i * width + j].isAlive = 0;
                }
            }
        }
    }
}

// Function to print the game of life board
void printBoard(Cell *cells, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (cells[i * width + j].isAlive) {
                printf("* ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

// Main function
int main() {
    // Initialize the random seed
    srand(time(NULL));

    // Define the size of the game board
    int width = 20;
    int height = 20;

    // Create a new array for the next generation
    Cell *newCells = (Cell *)malloc(width * height * sizeof(Cell));

    // Initialize the game board with random cells
    Cell *cells = (Cell *)malloc(width * height * sizeof(Cell));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (rand() % 2 == 1) {
                cells[i * width + j].isAlive = 1;
            } else {
                cells[i * width + j].isAlive = 0;
            }
        }
    }

    // Apply the rules of the game of life
    for (int i = 0; i < 100; i++) { // Run for 100 generations
        applyRules(cells, width, height, newCells);
        Cell *temp = cells;
        cells = newCells;
        newCells = temp;
    }

    // Print the final game of life board
    printBoard(cells, width, height);

    // Free memory
    free(newCells);
    free(cells);

    return 0;
}