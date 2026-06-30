#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure to represent a cell in the maze
typedef struct {
    int visited;
    int x, y; // coordinates of the cell
} Cell;

// Function to generate a random number between 0 and max-1
int random(int max) {
    return rand() % (max + 1);
}

// Function to print the maze
void printMaze(Cell** cells, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (cells[y][x].visited)
                printf("##");
            else
                printf("  ");
        }
        printf("\n");
    }
}

// Function to generate a random maze using depth-first search
void generateMaze(Cell** cells, int width, int height) {
    srand(time(NULL));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cells[y][x].visited = 0;
        }
    }

    int startX = random(width);
    int startY = random(height);

    Cell* currentCell = &cells[startY][startX];
    while (!currentCell->visited) {
        int directions[4] = {1, -1, width, -width};
        for (int i = 0; i < 4; i++) {
            int newX = currentCell->x + directions[i % 2];
            int newY = currentCell->y + directions[(i+1)%2];

            if (newX >= 0 && newX < width && newY >= 0 && newY < height &&
                !cells[newY][newX].visited) {
                cells[newY][newX].visited = 1;
                currentCell = &cells[newY][newX];
                break;
            }
        }
    }

    // Make sure the start and end are not visited
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if ((x == startX && y == startY) || (x == 0 && y == 0)) {
                cells[y][x].visited = 0;
            }
        }
    }
}

// Function to solve the maze
void solveMaze(Cell** cells, int width, int height) {
    printf("Enter your starting position (row, column): ");
    int startX, startY;
    scanf("%d %d", &startX, &startY);

    Cell* currentCell = &cells[startY][startX];
    while (!currentCell->visited) {
        int directions[4] = {1, -1, width, -width};
        for (int i = 0; i < 4; i++) {
            int newX = currentCell->x + directions[i % 2];
            int newY = currentCell->y + directions[(i+1)%2];

            if (newX >= 0 && newX < width && newY >= 0 && newY < height &&
                !cells[newY][newX].visited) {
                cells[newY][newX].visited = 1;
                currentCell = &cells[newY][newX];
                break;
            }
        }
    }

    printf("Congratulations, you have solved the maze!\n");
}

int main() {
    int width = 11, height = 7; // Change these values to change the size of the maze
    Cell** cells = (Cell**)malloc(height * sizeof(Cell*));
    for (int y = 0; y < height; y++) {
        cells[y] = (Cell*)malloc(width * sizeof(Cell));
        for (int x = 0; x < width; x++) {
            cells[y][x].visited = 0;
            cells[y][x].x = x;
            cells[y][x].y = y;
        }
    }

    generateMaze(cells, width, height);
    printMaze(cells, width, height);

    solveMaze(cells, width, height);

    for (int y = 0; y < height; y++) {
        free(cells[y]);
    }
    free(cells);

    return 0;
}