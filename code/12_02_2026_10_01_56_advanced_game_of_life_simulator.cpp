#include <iostream>
#include <vector>

// Class representing a cell in the Game of Life
class Cell {
public:
    bool alive; // Is the cell currently alive?

    Cell(bool isAlive) : alive(isAlive) {}
};

// Class representing a 2D grid for the Game of Life
class Grid {
private:
    std::vector<std::vector<Cell>> cells;
    int width, height;

public:
    // Constructor to initialize the grid with given dimensions and random cell states
    Grid(int w, int h) : width(w), height(h) {
        cells.resize(height);
        for (int i = 0; i < height; ++i) {
            cells[i].resize(width);
            for (int j = 0; j < width; ++j) {
                // Randomly set cell state
                cells[i][j] = Cell((rand() % 2 == 1));
            }
        }
    }

    // Apply Conway's rules to update the grid
    void applyRules(int iterations = 1) {
        std::vector<std::vector<Cell>> newGrid(cells);
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int liveNeighbors = countLiveNeighbors(i, j);
                if (cells[i][j].alive && (liveNeighbors < 2 || liveNeighbors > 3)) {
                    newGrid[i][j] = Cell(false); // Die due to underpopulation or overpopulation
                } else if (!cells[i][j].alive && liveNeighbors == 3) {
                    newGrid[i][j] = Cell(true); // Birth from underpopulation
                } else {
                    newGrid[i][j] = cells[i][j]; // Stay the same, no change
                }
            }
        }
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                cells[i][j] = newGrid[i][j];
            }
        }

        // Repeat the process for the specified number of iterations
        for (int i = 0; i < iterations - 1; ++i) {
            applyRules();
        }
    }

    // Helper function to count live neighbors for a given cell
    int countLiveNeighbors(int i, int j) {
        int count = 0;
        for (int x = -1; x <= 1; ++x) {
            for (int y = -1; y <= 1; ++y) {
                if ((x == 0 && y == 0) || i + x < 0 || j + y < 0 || i + x >= height || j + y >= width) continue;
                count += cells[i + x][j + y].alive ? 1 : 0;
            }
        }
        return count;
    }

    // Print the current state of the grid
    void printGrid() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::cout << (cells[i][j].alive ? "*" : " ") << " ";
            }
            std::cout << "\n";
        }
    }

};

int main() {
    // Create a grid with dimensions 20x20
    Grid game(20, 20);

    // Run the Game of Life for 10 iterations and print each step
    for (int i = 0; i < 10; ++i) {
        game.printGrid();
        game.applyRules();
    }

    return 0;
}