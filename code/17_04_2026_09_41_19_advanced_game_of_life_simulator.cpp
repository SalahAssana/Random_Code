#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <random>

using namespace std;

// Define constants for the game of life
const int WIDTH = 80;
const int HEIGHT = 25;
const char ALIVE = '*';
const char DEAD = ' ';

class Cell {
public:
    bool isAlive;
    int neighbors;

    Cell() : isAlive(false), neighbors(0) {}
};

class GameOfLife {
private:
    vector<vector<Cell>> grid;
    mutex mtx;
    random_device rd;
    mt19937 gen(rd());

public:
    GameOfLife(int width, int height) {
        grid.resize(height, vector<Cell>(width));
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (gen() % 2 == 1) {
                    grid[i][j].isAlive = true;
                } else {
                    grid[i][j].isAlive = false;
                }
            }
        }
    }

    void update() {
        vector<vector<Cell>> newGrid(grid);
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                int neighborsCount = countNeighbors(i, j);
                if (grid[i][j].isAlive) {
                    if (neighborsCount < 2 || neighborsCount > 3) {
                        newGrid[i][j].isAlive = false;
                    }
                } else {
                    if (neighborsCount == 3) {
                        newGrid[i][j].isAlive = true;
                    }
                }
            }
        }
        grid = move(newGrid);
    }

    void print() {
        lock_guard<mutex> lock(mtx);
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j].isAlive) {
                    cout << ALIVE;
                } else {
                    cout << DEAD;
                }
            }
            cout << endl;
        }
    }

    int countNeighbors(int x, int y) {
        int count = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                int newX = x + i;
                int newY = y + j;
                if (newX >= 0 && newX < grid.size() && newY >= 0 && newY < grid[0].size()) {
                    count += (grid[newX][newY].isAlive ? 1 : 0);
                }
            }
        }
        return count;
    }

};

int main() {
    GameOfLife game(WIDTH, HEIGHT);

    while (true) {
        game.print();
        this_thread::sleep_for(chrono::milliseconds(500));
        game.update();
    }

    return 0;
}