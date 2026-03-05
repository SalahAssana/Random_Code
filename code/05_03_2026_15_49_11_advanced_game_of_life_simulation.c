#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 20

// Define a struct to represent a cell in the Game of Life grid
typedef struct {
    int alive;
    int neighbors;
} Cell;

// Function to initialize the game state with random cells
void initGame(Cell** grid) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j].alive = rand() % 2;
        }
    }
}

// Function to count the number of alive neighbors for a cell
void countNeighbors(Cell** grid, int x, int y, Cell* cell) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < HEIGHT && ny >= 0 && ny < WIDTH) {
                count += grid[nx][ny].alive;
            }
        }
    }
    cell->neighbors = count;
}

// Function to apply the rules of the Game of Life
void updateGame(Cell** grid, Cell* cell) {
    if (cell->alive == 1) {
        if (cell->neighbors < 2 || cell->neighbors > 3) {
            cell->alive = 0; // Die from underpopulation or overpopulation
        }
    } else {
        if (cell->neighbors == 3) {
            cell->alive = 1; // Become alive from the neighborhood
        }
    }
}

// Function to print the game state as ASCII art
void printGame(Cell** grid) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j].alive == 1) printf("* ");
            else printf(". ");
        }
        printf("\n");
    }
}

// Main function to run the Game of Life simulation
int main() {
    srand(time(NULL)); // Seed random number generator

    Cell** grid = (Cell**)malloc(HEIGHT * sizeof(Cell*));
    for (int i = 0; i < HEIGHT; i++) {
        grid[i] = (Cell*)malloc(WIDTH * sizeof(Cell));
    }

    initGame(grid);

    for (int generation = 0; generation < 10; generation++) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                countNeighbors(grid, i, j, &grid[i][j]);
            }
        }
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                updateGame(grid, &grid[i][j]);
            }
        }
        printGame(grid);
        printf("Generation %d\n", generation + 1);
    }

    for (int i = 0; i < HEIGHT; i++) free(grid[i]);
    free(grid);

    return 0;
}