#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

class Cell {
public:
    bool alive;
};

class Grid {
private:
    vector<vector<Cell>> cells;
    int width, height;

public:
    Grid(int w, int h) : width(w), height(h) {
        cells.resize(height);
        for (int i = 0; i < height; ++i)
            cells[i].resize(width);
    }

    void print() const {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j)
                cout << (cells[i][j].alive ? '*' : ' ');
            cout << endl;
        }
    }

    void evolve() {
        vector<vector<Cell>> nextCells(height, vector<Cell>(width));
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                int aliveNeighbors = countAliveNeighbors(i, j);
                if (cells[i][j].alive && (aliveNeighbors == 2 || aliveNeighbors == 3))
                    nextCells[i][j].alive = true;
                else if (!cells[i][j].alive && aliveNeighbors == 3)
                    nextCells[i][j].alive = true;
                else
                    nextCells[i][j].alive = false;
            }
        }
        cells = move(nextCells);
    }

private:
    int countAliveNeighbors(int i, int j) const {
        int count = 0;
        for (int x = -1; x <= 1; ++x) {
            for (int y = -1; y <= 1; ++y) {
                int neighborI = i + x;
                int neighborJ = j + y;
                if (neighborI >= 0 && neighborI < height && neighborJ >= 0 && neighborJ < width)
                    count += cells[neighborI][neighborJ].alive ? 1 : 0;
            }
        }
        return count - (cells[i][j].alive ? 1 : 0);
    }
};

int main() {
    Grid grid(20, 10);

    // Initial state
    for (int i = 0; i < 5; ++i) {
        grid.cells[2 + i][3] = {true};
        grid.cells[2 + i][4] = {true};
        grid.cells[2 + i][5] = {true};
    }

    // Run the game
    while (true) {
        grid.print();
        this_thread::sleep_for(chrono::milliseconds(500));
        grid.evolve();
    }

    return 0;
}