#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Cell {
public:
    bool isAlive;
    int neighbors;

    Cell() : isAlive(false), neighbors(0) {}
};

class GameOfLife {
private:
    vector<vector<Cell>> grid;
    int width, height;

public:
    GameOfLife(int w, int h) : width(w), height(h) {
        for (int i = 0; i < height; i++) {
            vector<Cell> row;
            for (int j = 0; j < width; j++) {
                row.push_back(Cell());
            }
            grid.push_back(row);
        }
    }

    void setCell(int x, int y, bool alive) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid[y][x].isAlive = alive;
        }
    }

    void printGrid() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (grid[i][j].isAlive) {
                    cout << "* ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    }

    void nextGeneration() {
        vector<vector<Cell>> newGrid(grid);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int liveNeighbors = countLiveNeighbors(i, j);
                if (grid[i][j].isAlive) {
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        newGrid[i][j].isAlive = false;
                    }
                } else {
                    if (liveNeighbors == 3) {
                        newGrid[i][j].isAlive = true;
                    }
                }
            }
        }
        grid = newGrid;
    }

    int countLiveNeighbors(int x, int y) {
        int liveCount = 0;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;
                int nx = x + i;
                int ny = y + j;
                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    liveCount += grid[ny][nx].isAlive ? 1 : 0;
                }
            }
        }
        return liveCount;
    }

    void run(int generations) {
        srand(time(0));
        for (int i = 0; i < generations; i++) {
            printGrid();
            nextGeneration();
            cout << endl;
        }
    }
};

int main() {
    GameOfLife game(20, 20);
    game.setCell(10, 10, true);
    game.run(5);
    return 0;
}