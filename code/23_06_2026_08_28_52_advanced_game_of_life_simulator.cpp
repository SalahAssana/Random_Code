#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Define the Game of Life class
class GameOfLife {
public:
    // Constructor to initialize the game board and set initial state
    GameOfLife(int rows, int cols) : rows_(rows), cols_(cols), board_(rows, vector<bool>(cols)) {}

    // Run the game for a specified number of generations
    void runGame(int generations) {
        // Create a queue to hold cells that need to be updated
        queue<pair<int, int>> updateQueue;

        // Initialize the game state based on initial conditions
        initialize();

        // Simulate each generation
        for (int i = 0; i < generations; ++i) {
            // Update all cells in a single pass
            while (!updateQueue.empty()) {
                int row = updateQueue.front().first;
                int col = updateQueue.front().second;
                updateQueue.pop();

                // Apply the Game of Life rules to determine new state
                bool newState = applyRules(row, col);

                // Update the board and queue if necessary
                if (newState != board_[row][col]) {
                    board_[row][col] = newState;
                    if (newState) {
                        updateQueue.push({ row, col });
                    }
                }
            }
        }
    }

    // Initialize the game state based on initial conditions
    void initialize() {
        // Add your initialization code here
    }

    // Apply the Game of Life rules to determine new state
    bool applyRules(int row, int col) {
        int liveNeighbors = 0;

        // Count the number of live neighbors
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if ((i == 0 && j == 0) || row + i < 0 || col + j >= cols_ || row + i >= rows_) continue;
                liveNeighbors += board_[row + i][col + j];
            }
        }

        // Apply the Game of Life rules
        return (board_[row][col] && (liveNeighbors == 2 || liveNeighbors == 3)) ||
               (!board_[row][col] && liveNeighbors == 3);
    }

private:
    int rows_;
    int cols_;
    vector<vector<bool>> board_;
};

int main() {
    // Create a Game of Life simulator with an 11x11 grid
    GameOfLife game(11, 11);

    // Run the game for 10 generations
    game.runGame(10);

    return 0;
}