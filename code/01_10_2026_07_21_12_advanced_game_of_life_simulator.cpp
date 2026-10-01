#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

// Structure to represent a cell in the Game of Life
struct Cell {
    bool isAlive;
    int neighbors; // Number of alive neighbors
};

// Function to count the number of alive neighbors for a given cell
int countNeighbors(const vector<vector<Cell>>& grid, int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (!(i == 0 && j == 0)) { // Skip the current cell
                int newRow = row + i;
                int newCol = col + j;
                if (newRow >= 0 && newRow < grid.size() && newCol >= 0 && newCol < grid[0].size()) {
                    count += grid[newRow][newCol].isAlive ? 1 : 0;
                }
            }
        }
    }
    return count;
}

// Function to apply the Game of Life rules
void applyRules(vector<vector<Cell>>& grid) {
    vector<vector<Cell>> newGrid = grid; // Create a copy of the current grid

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            Cell& cell = grid[i][j];
            int neighbors = countNeighbors(grid, i, j);
            if (cell.isAlive) { // Cell is alive
                if (neighbors < 2 || neighbors > 3) {
                    newGrid[i][j].isAlive = false; // Die from underpopulation or overpopulation
                }
            } else { // Cell is dead
                if (neighbors == 3) {
                    newGrid[i][j].isAlive = true; // Become alive from nearby live cells
                }
            }
        }
    }

    grid = move(newGrid); // Replace the original grid with the new one
}

// Function to print the Game of Life grid
void printGrid(const vector<vector<Cell>>& grid) {
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j].isAlive) {
                cout << "* ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

int main() {
    int rows = 20, cols = 20; // Size of the Game of Life grid
    vector<vector<Cell>> grid(rows, vector<Cell>(cols)); // Initialize the grid

    // Randomly initialize some cells as alive
    srand(time(0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((rand() % 100) < 50) { // 50% chance of being alive
                grid[i][j].isAlive = true;
            } else {
                grid[i][j].isAlive = false;
            }
        }
    }

    for (int i = 0; i < 10; ++i) { // Run the Game of Life for 10 generations
        applyRules(grid);
        printGrid(grid);
        cout << endl;
        sleep(1); // Pause between generations
    }

    return 0;
}