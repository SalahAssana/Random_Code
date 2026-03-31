#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

// Grid size constant
const int GRID_SIZE = 50;

class GameOfLife {
public:
    GameOfLife() : grid(GRID_SIZE, std::vector<bool>(GRID_SIZE)) {}

    void updateGrid();
    void printGrid();

private:
    std::vector<std::vector<bool>> grid;
};

void GameOfLife::updateGrid() {
    std::vector<std::vector<bool>> newGrid(GRID_SIZE, std::vector<bool>(GRID_SIZE));

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int liveNeighbors = countLiveNeighbors(i, j);
            if (grid[i][j]) {
                // Cell is alive
                newGrid[i][j] = (liveNeighbors == 2 || liveNeighbors == 3) ? true : false;
            } else {
                // Cell is dead
                newGrid[i][j] = (liveNeighbors == 3) ? true : false;
            }
        }
    }

    grid = newGrid;
}

int GameOfLife::countLiveNeighbors(int i, int j) {
    int count = 0;

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if ((x == 0 && y == 0) || i + x < 0 || j + y < 0 || i + x >= GRID_SIZE || j + y >= GRID_SIZE) continue;
            count += grid[i + x][j + y] ? 1 : 0;
        }
    }

    return count;
}

void GameOfLife::printGrid() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            std::cout << grid[i][j] ? "*" : " ";
        }
        std::cout << "\n";
    }
}

int main() {
    GameOfLife game;
    game.grid[GRID_SIZE / 2][GRID_SIZE / 2] = true;

    while (true) {
        game.updateGrid();
        game.printGrid();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}