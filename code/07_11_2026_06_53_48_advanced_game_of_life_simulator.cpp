#include <iostream>
#include <vector>
#include <thread>

using namespace std;

const int width = 20;
const int height = 20;

// Data structure to represent a cell in the Game of Life
struct Cell {
    bool alive;
};

// Grid class to hold the state of the cells and perform operations on it
class Grid {
public:
    vector<vector<Cell>> grid;
    int width, height;

    // Constructor to initialize the grid with random values
    Grid() : width(width), height(height) {
        grid.resize(height);
        for (int i = 0; i < height; i++) {
            grid[i].resize(width);
            for (int j = 0; j < width; j++) {
                grid[i][j] = {rand() % 2 == 1};
            }
        }
    }

    // Method to print the current state of the grid
    void printGrid() {
        cout << "Current State:\n";
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (grid[i][j].alive) {
                    cout << "* ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    }

    // Method to evolve the grid according to the Game of Life rules
    void evolve() {
        vector<vector<Cell>> nextGrid(grid);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int liveNeighbors = countLiveNeighbors(i, j);
                if (grid[i][j].alive) {
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        nextGrid[i][j] = {false};
                    } else {
                        nextGrid[i][j] = {true};
                    }
                } else {
                    if (liveNeighbors == 3) {
                        nextGrid[i][j] = {true};
                    } else {
                        nextGrid[i][j] = {false};
                    }
                }
            }
        }
        grid = nextGrid;
    }

    // Helper method to count the number of live neighbors for a cell
    int countLiveNeighbors(int i, int j) {
        int count = 0;
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if ((x == 0 && y == 0) || i + x < 0 || i + x >= height || j + y < 0 || j + y >= width) continue;
                if (grid[i + x][j + y].alive) count++;
            }
        }
        return count;
    }
};

// Main function to create a Game of Life simulator
int main() {
    Grid gameOfLife;
    while (true) {
        gameOfLife.printGrid();
        this_thread::sleep_for(chrono::milliseconds(1000));
        gameOfLife.evolve();
    }
    return 0;
}