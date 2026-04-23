#include <stdio.h>
#include <stdlib.h>

// Define structure for cell
typedef struct {
    int isAlive;
    int neighbors[8];
} Cell;

// Function to count alive neighbors of a cell
int countAliveNeighbors(Cell *cell) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (cell->neighbors[i] == 1)
            count++;
    }
    return count;
}

// Function to update the game of life based on rules
void updateGameOfLife(Cell **grid, int rows, int cols) {
    Cell *newGrid = (Cell *)malloc(rows * sizeof(Cell *));
    for (int i = 0; i < rows; i++) {
        newGrid[i] = (Cell *)malloc(cols * sizeof(Cell));
    }
    
    // Iterate over each cell in the grid
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            Cell *cell = &grid[i][j];
            
            int aliveNeighbors = countAliveNeighbors(cell);
            
            // Rule 1: Any live cell with fewer than two live neighbors dies.
            if (cell->isAlive && aliveNeighbors < 2)
                newGrid[i][j].isAlive = 0;
            
            // Rule 3: Any live cell with more than three live neighbors dies.
            else if (cell->isAlive && aliveNeighbors > 3)
                newGrid[i][j].isAlive = 0;
            
            // Rule 4: Any dead cell with exactly three live neighbors becomes a live cell.
            else if (!cell->isAlive && aliveNeighbors == 3)
                newGrid[i][j].isAlive = 1;
            
            // If the cell is not changing, keep it as it is
            else
                newGrid[i][j] = *cell;
        }
    }
    
    // Copy the updated grid to the original grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = newGrid[i][j];
        }
    }
    
    // Free the memory allocated for the temporary grid
    for (int i = 0; i < rows; i++) {
        free(newGrid[i]);
    }
    free(newGrid);
}

// Function to print the game of life grid
void printGameOfLife(Cell **grid, int rows, int cols) {
    // Print each row of the grid
    for (int i = 0; i < rows; i++) {
        // Print each cell in the row
        for (int j = 0; j < cols; j++) {
            Cell *cell = &grid[i][j];
            if (cell->isAlive)
                printf("1 ");
            else
                printf("0 ");
        }
        printf("\n");
    }
}

// Function to initialize the game of life grid with random cells
void initializeGameOfLife(Cell **grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Cell *cell = &grid[i][j];
            cell->isAlive = rand() % 2;
            // Initialize neighbors of the cell
            int direction = 1;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    if ((k == 0 && l == 0) || i + k < 0 || j + l < 0 || i + k >= rows || j + l >= cols)
                        continue;
                    cell->neighbors[direction] = (grid[i + k][j + l]).isAlive;
                    direction++;
                }
            }
        }
    }
}

// Main function
int main() {
    srand(time(NULL));
    
    int rows = 20, cols = 20;
    
    Cell **grid = (Cell **)malloc(rows * sizeof(Cell *));
    for (int i = 0; i < rows; i++) {
        grid[i] = (Cell *)malloc(cols * sizeof(Cell));
    }
    
    initializeGameOfLife(grid, rows, cols);
    
    for (int generation = 0; generation < 10; generation++) {
        printf("Generation %d:\n", generation);
        printGameOfLife(grid, rows, cols);
        updateGameOfLife(grid, rows, cols);
    }
    
    // Free the memory allocated for the grid
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
    
    return 0;
}