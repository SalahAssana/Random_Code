#include <iostream>
#include <vector>
#include <algorithm>

// Structure to represent a cell in the Game of Life
struct Cell {
    bool alive;
};

class GameOfLife {
public:
    // Constructor to initialize the game grid with random values
    GameOfLife(int rows, int cols) : rows_(rows), cols_(cols), grid_(rows, std::vector<Cell>(cols)) {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                if (rand() % 2) { // Randomly set cell to alive or dead
                    grid_[i][j].alive = true;
                }
            }
        }
    }

    // Method to print the current state of the game grid
    void printGrid() const {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                std::cout << (grid_[i][j].alive ? "X" : ".") << " ";
            }
            std::cout << std::endl;
        }
    }

    // Method to simulate the next generation of the Game of Life
    void nextGeneration() {
        grid_.resize(rows_, cols_);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                int liveNeighbors = countLiveNeighbors(i, j);
                if (grid_[i][j].alive && (liveNeighbors < 2 || liveNeighbors > 3)) {
                    grid_[i][j].alive = false;
                } else if (!grid_[i][j].alive && liveNeighbors == 3) {
                    grid_[i][j].alive = true;
                }
            }
        }
    }

private:
    int countLiveNeighbors(int row, int col) const {
        int count = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newRow = row + i;
                int newCol = col + j;
                if (newRow >= 0 && newRow < rows_ && newCol >= 0 && newCol < cols_ &&
                    grid_[newRow][newCol].alive) {
                    ++count;
                }
            }
        }
        // Subtract self
        if (grid_[row][col].alive) {
            --count;
        }
        return count;
    }

    int rows_;
    int cols_;
    std::vector<std::vector<Cell>> grid_;
};

int main() {
    GameOfLife game(20, 20);
    for (int i = 0; i < 10; ++i) {
        game.printGrid();
        game.nextGeneration();
    }
    return 0;
}