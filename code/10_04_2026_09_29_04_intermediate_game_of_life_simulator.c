#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WIDTH 100
#define MAX_HEIGHT 100
#define CELL_ALIVE 1
#define CELL_DEAD 0
#define SPEED 10 // milliseconds

typedef struct {
    int x, y;
} Cell;

void printGrid(int grid[][MAX_HEIGHT], int width) {
    printf("\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (grid[i][j] == CELL_ALIVE)
                printf("* ");
            else
                printf(". ");
        }
        printf("\n");
    }
}

void countNeighbors(int grid[][MAX_HEIGHT], int x, int y, int* alive) {
    *alive = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if ((i == 0 && j == 0) || x + i < 0 || y + j < 0 || x + i >= width || y + j >= height)
                continue;
            *alive += grid[y + j][x + i];
        }
    }
}

void updateGrid(int grid[][MAX_HEIGHT], int width, int height, int speed) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int alive = 0;
            countNeighbors(grid, j, i, &alive);
            if ((grid[i][j] == CELL_ALIVE && (alive < 2 || alive > 3)) ||
                (grid[i][j] == CELL_DEAD && alive == 3))
                grid[i][j] = !grid[i][j];
        }
    }
}

int main() {
    srand(time(NULL)); // seed random number generator
    int width, height;
    printf("Enter the width of the grid: ");
    scanf("%d", &width);
    printf("Enter the height of the grid: ");
    scanf("%d", &height);

    if (width > MAX_WIDTH || height > MAX_HEIGHT) {
        printf("Grid size exceeds maximum limits. Using default size.\n");
        width = MAX_WIDTH;
        height = MAX_HEIGHT;
    }

    int grid[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (rand() % 2)
                grid[i][j] = CELL_ALIVE;
            else
                grid[i][j] = CELL_DEAD;
        }
    }

    int speed;
    printf("Enter the speed of the simulation in milliseconds: ");
    scanf("%d", &speed);

    while (1) {
        printGrid(grid, width);
        updateGrid(grid, width, height, speed);
        usleep(speed * 1000); // pause for specified time
    }

    return 0;
}