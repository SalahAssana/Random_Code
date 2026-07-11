#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a puzzle
typedef struct {
    int rows;
    int cols;
    char **grid;
} Puzzle;

// Function to generate a random puzzle grid
Puzzle* generatePuzzle(int rows, int cols) {
    Puzzle* puzzle = (Puzzle*)malloc(sizeof(Puzzle));
    puzzle->rows = rows;
    puzzle->cols = cols;
    puzzle->grid = (char**)malloc(rows * sizeof(char*));
    
    for (int i = 0; i < rows; i++) {
        puzzle->grid[i] = (char*)malloc(cols * sizeof(char));
        
        for (int j = 0; j < cols; j++) {
            // Randomly set a value for each cell
            if (rand() % 2 == 0) {
                puzzle->grid[i][j] = 'X';
            } else {
                puzzle->grid[i][j] = ' ';
            }
        }
    }
    
    return puzzle;
}

// Function to solve the puzzle
void solvePuzzle(Puzzle* puzzle) {
    for (int i = 0; i < puzzle->rows; i++) {
        for (int j = 0; j < puzzle->cols; j++) {
            // Check if the cell is 'X' and there are no more 'X's to its left
            if (puzzle->grid[i][j] == 'X' && j > 0) {
                int k = j - 1;
                
                while (k >= 0 && puzzle->grid[i][k] != ' ') {
                    k--;
                }
                
                if (k < 0) {
                    // If there are no more 'X's to the left, set this cell as 'X'
                    puzzle->grid[i][j] = 'X';
                } else {
                    // Otherwise, set this cell as a space
                    puzzle->grid[i][j] = ' ';
                }
            }
        }
    }
}

int main() {
    srand(time(NULL));  // Seed random number generator
    
    Puzzle* puzzle = generatePuzzle(5, 5);
    
    printf("Generated Puzzle:\n");
    for (int i = 0; i < puzzle->rows; i++) {
        for (int j = 0; j < puzzle->cols; j++) {
            printf("%c ", puzzle->grid[i][j]);
        }
        printf("\n");
    }
    
    solvePuzzle(puzzle);
    
    printf("Solved Puzzle:\n");
    for (int i = 0; i < puzzle->rows; i++) {
        for (int j = 0; j < puzzle->cols; j++) {
            printf("%c ", puzzle->grid[i][j]);
        }
        printf("\n");
    }
    
    // Free the memory
    for (int i = 0; i < puzzle->rows; i++) {
        free(puzzle->grid[i]);
    }
    free(puzzle->grid);
    free(puzzle);
    
    return 0;
}