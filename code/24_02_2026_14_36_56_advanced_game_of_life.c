#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the structure for a cell
typedef struct {
    int is_alive;
    int x;
    int y;
} Cell;

// Function to initialize the game of life grid
void init_grid(Cell **grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j].is_alive = rand() % 2;
            grid[i][j].x = i;
            grid[i][j].y = j;
        }
    }
}

// Function to print the game of life grid
void print_grid(Cell **grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j].is_alive) {
                printf("* ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

// Function to count the number of alive neighbors
int count_neighbors(Cell **grid, int rows, int cols, Cell *cell) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if ((i == 0 && j == 0) || i + cell->x >= rows || j + cell->y >= cols || i + cell->x < 0 || j + cell->y < 0)
                continue;
            count += grid[i + cell->x][j + cell->y].is_alive;
        }
    }
    return count;
}

// Function to update the game of life grid
void update_grid(Cell **grid, int rows, int cols) {
    Cell *temp = (Cell *)malloc((rows * cols) * sizeof(Cell));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            temp[i * cols + j].is_alive = grid[i][j].is_alive;
        }
    }

    free(grid);

    int new_rows = rows, new_cols = cols;

    if (new_rows < 5 || new_cols < 5) {
        printf("Grid size too small. Minimum is 5x5.\n");
        return;
    }

    for (int i = 0; i < new_rows; i++) {
        for (int j = 0; j < new_cols; j++) {
            int neighbors = count_neighbors(grid, rows, cols, &temp[i * new_cols + j]);
            if (grid[i][j].is_alive) {
                temp[i * new_cols + j].is_alive = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                temp[i * new_cols + j].is_alive = (neighbors == 3) ? 1 : 0;
            }
        }
    }

    grid = &temp;

    free(temp);
}

int main() {
    srand(time(NULL));

    int rows = 20, cols = 20; // Grid size
    Cell **grid = (Cell **)malloc(rows * sizeof(Cell *));
    for (int i = 0; i < rows; i++) {
        grid[i] = (Cell *)malloc(cols * sizeof(Cell));
    }

    init_grid(grid, rows, cols);

    print_grid(grid, rows, cols);

    int steps = 100;
    for (int i = 0; i < steps; i++) {
        update_grid(grid, rows, cols);
        printf("\n");
        print_grid(grid, rows, cols);
    }

    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}