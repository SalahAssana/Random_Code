#include <stdio.h>
#include <stdlib.h>

#define WIDTH 20
#define HEIGHT 20

typedef struct {
    int alive;
} Cell;

void printGrid(Cell grid[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j].alive) {
                printf("* ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void updateGrid(Cell grid[HEIGHT][WIDTH]) {
    Cell newGrid[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int liveNeighbors = 0;
            if ((i > 0) && grid[i-1][j].alive) liveNeighbors++;
            if ((i < HEIGHT - 1) && grid[i+1][j].alive) liveNeighbors++;
            if ((j > 0) && grid[i][j-1].alive) liveNeighbors++;
            if ((j < WIDTH - 1) && grid[i][j+1].alive) liveNeighbors++;
            if ((i > 0) && (j > 0) && grid[i-1][j-1].alive) liveNeighbors++;
            if ((i > 0) && (j < WIDTH - 1) && grid[i-1][j+1].alive) liveNeighbors++;
            if ((i < HEIGHT - 1) && (j > 0) && grid[i+1][j-1].alive) liveNeighbors++;
            if ((i < HEIGHT - 1) && (j < WIDTH - 1) && grid[i+1][j+1].alive) liveNeighbors++;
            if ((i == 0) || (i == HEIGHT - 1) || (j == 0) || (j == WIDTH - 1)) {
                newGrid[i][j].alive = grid[i][j].alive;
            } else if (grid[i][j].alive && (liveNeighbors < 2 || liveNeighbors > 3)) {
                newGrid[i][j].alive = 0;
            } else if (!grid[i][j].alive && (liveNeighbors == 3)) {
                newGrid[i][j].alive = 1;
            } else {
                newGrid[i][j].alive = grid[i][j].alive;
            }
        }
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = newGrid[i][j];
        }
    }
}

void initGrid(Cell grid[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if ((i > 5) && (i < 15)) {
                if ((j > 2) && (j < 17)) {
                    grid[i][j].alive = 1;
                } else {
                    grid[i][j].alive = 0;
                }
            } else {
                grid[i][j].alive = 0;
            }
        }
    }
}

int main() {
    Cell grid[HEIGHT][WIDTH];
    initGrid(grid);
    for (int i = 0; i < 5; i++) {
        printGrid(grid);
        updateGrid(grid);
        printf("\n");
    }
    return 0;
}