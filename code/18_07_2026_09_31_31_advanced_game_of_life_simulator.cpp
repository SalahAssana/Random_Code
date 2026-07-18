#include <iostream>
#include <vector>
#include <algorithm>

// Game of Life Simulator Class
class GameOfLife {
public:
    // Constructor to initialize grid size and random cell state
    GameOfLife(int rows, int cols) : rows_(rows), cols_(cols), grid_(rows, std::vector<bool>(cols)) {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                // Randomly set cell state
                grid_[i][j] = rand() % 2 == 0;
            }
        }
    }

    // Function to print the current state of the grid
    void printGrid() const {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                std::cout << (grid_[i][j] ? '*' : ' ');
            }
            std::cout << '\n';
        }
    }

    // Function to update the grid state according to Game of Life rules
    void nextGeneration() {
        std::vector<std::vector<bool>> newGrid(rows_, std::vector<bool>(cols_));
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                int liveNeighbors = countLiveNeighbors(i, j);
                if (grid_[i][j] && (liveNeighbors == 2 || liveNeighbors == 3)) {
                    newGrid[i][j] = true;
                } else if (!grid_[i][j] && liveNeighbors == 3) {
                    newGrid[i][j] = true;
                } else {
                    newGrid[i][j] = false;
                }
            }
        }
        grid_ = newGrid;
    }

private:
    int rows_;
    int cols_;
    std::vector<std::vector<bool>> grid_;

    // Function to count the number of live neighbors for a given cell
    int countLiveNeighbors(int row, int col) const {
        int count = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newRow = row + i;
                int newCol = col + j;
                if ((newRow >= 0 && newRow < rows_ && newCol >= 0 && newCol < cols_) &&
                    grid_[newRow][newCol]) {
                    ++count;
                }
            }
        }
        // Subtract the cell itself from the count
        if (grid_[row][col]) {
            --count;
        }
        return count;
    }

};

int main() {
    srand(time(0));
    GameOfLife game(10, 10);
    for (int i = 0; i < 5; ++i) {
        game.printGrid();
        game.nextGeneration();
        std::cout << '\n';
    }
    return 0;
}
