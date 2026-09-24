#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Game of Life Cell
class Cell {
public:
    bool alive;
    int neighbors;

    Cell() : alive(false), neighbors(0) {}
};

// Game of Life Grid
class Grid {
private:
    vector<vector<Cell>> cells;
    int width, height;

public:
    Grid(int w, int h) : width(w), height(h) {
        cells.resize(height);
        for (int i = 0; i < height; ++i) {
            cells[i].resize(width);
            fill(cells[i].begin(), cells[i].end(), Cell());
        }
    }

    void setAlive(int x, int y, bool alive) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            cells[y][x].alive = alive;
        }
    }

    void countNeighbors() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int neighbors = 0;
                // Check all eight directions
                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        if (i + y >= 0 && i + y < height && j + x >= 0 && j + x < width) {
                            neighbors += cells[i + y][j + x].alive ? 1 : 0;
                        }
                    }
                }
                // Store the count
                cells[i][j].neighbors = neighbors;
            }
        }
    }

    void nextGeneration() {
        Grid newGrid(width, height);
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int liveNeighbors = cells[i][j].neighbors;
                if (cells[i][j].alive) {
                    // Any live cell with fewer than two live neighbors dies, as if by underpopulation.
                    // Any live cell with two or three live neighbors lives on to the next generation.
                    // Any live cell with more than three live neighbors dies, as if by overpopulation.
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        newGrid.setAlive(j, i, false);
                    } else {
                        newGrid.setAlive(j, i, true);
                    }
                } else {
                    // Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
                    if (liveNeighbors == 3) {
                        newGrid.setAlive(j, i, true);
                    } else {
                        newGrid.setAlive(j, i, false);
                    }
                }
            }
        }
        cells = newGrid.cells;
    }

    void print() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                cout << (cells[i][j].alive ? "1" : "0") << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Grid grid(10, 10);
    // Initialize the grid
    for (int i = 4; i < 6; ++i) {
        for (int j = 4; j < 6; ++j) {
            grid.setAlive(j, i, true);
        }
    }

    // Run 10 generations
    for (int i = 0; i < 10; ++i) {
        grid.countNeighbors();
        grid.nextGeneration();
        cout << "Generation " << i + 1 << ":" << endl;
        grid.print();
        cout << endl;
    }

    return 0;
}