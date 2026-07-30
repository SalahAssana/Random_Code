#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 20; // size of the grid
const int GENERATIONS = 1000;
const char DEAD = ' ';
const char ALIVE = '*';

// Grid class to represent the Game of Life board
class Grid {
public:
    vector<vector<char>> cells;
    int width, height;

    Grid(int w, int h) : width(w), height(h) {
        cells.resize(height);
        for (int i = 0; i < height; ++i) {
            cells[i].resize(width, DEAD);
        }
    }

    void setCell(int x, int y, char c) { cells[y][x] = c; }
    char getCell(int x, int y) { return cells[y][x]; }
};

// Rule class to encapsulate the Game of Life rules
class Rule {
public:
    int countNeighbors(const Grid& grid, int x, int y) {
        int count = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                int nx = x + i, ny = y + j;
                if (nx >= 0 && nx < grid.width && ny >= 0 && ny < grid.height) {
                    count += grid.getCell(nx, ny) == ALIVE ? 1 : 0;
                }
            }
        }
        return count;
    }

    char applyRules(const Grid& grid, int x, int y) {
        int liveNeighbors = countNeighbors(grid, x, y);
        if (grid.getCell(x, y) == ALIVE && (liveNeighbors < 2 || liveNeighbors > 3)) {
            return DEAD; // underpopulation or overpopulation
        } else if (grid.getCell(x, y) == DEAD && liveNeighbors == 3) {
            return ALIVE; // birth
        }
        return grid.getCell(x, y); // stay the same
    }
};

// Game class to encapsulate the main game logic
class Game {
public:
    Grid grid;
    Rule rule;

    Game(int w, int h) : grid(w, h), rule() {}

    void play(int generations) {
        for (int i = 0; i < generations; ++i) {
            // update all cells
            for (int y = 0; y < grid.height; ++y) {
                for (int x = 0; x < grid.width; ++x) {
                    char newState = rule.applyRules(grid, x, y);
                    if (newState == ALIVE) {
                        // print alive cells
                        cout << "*";
                    } else {
                        cout << " ";
                    }
                }
                cout << endl;
            }
        }
    }
};

int main() {
    Game game(N, N); // initialize the game with a 20x20 grid
    game.play(GENERATIONS);
    return 0;
}