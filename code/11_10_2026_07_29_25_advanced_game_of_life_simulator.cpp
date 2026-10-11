#include <iostream>
#include <vector>

class Cell {
public:
    bool isAlive;
    int x, y;

    Cell(int x, int y) : x(x), y(y), isAlive(false) {}
};

class GameOfLife {
private:
    std::vector<std::vector<Cell>> cells;
    int width, height;

public:
    GameOfLife(int width, int height) : width(width), height(height) {}

    void setCellAlive(int x, int y, bool isAlive) {
        if (x < 0 || x >= width || y < 0 || y >= height) return;
        cells[y][x].isAlive = isAlive;
    }

    void nextGeneration() {
        std::vector<std::vector<Cell>> newCells(width, std::vector<Cell>(height));

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int liveNeighbors = countLiveNeighbors(x, y);
                if (cells[y][x].isAlive) {
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        newCells[y][x].isAlive = false;
                    } else {
                        newCells[y][x].isAlive = true;
                    }
                } else {
                    if (liveNeighbors == 3) {
                        newCells[y][x].isAlive = true;
                    } else {
                        newCells[y][x].isAlive = false;
                    }
                }
            }
        }

        cells = newCells;
    }

    int countLiveNeighbors(int x, int y) {
        int liveNeighbors = 0;

        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx == 0 && dy == 0) continue;
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    liveNeighbors += cells[ny][nx].isAlive ? 1 : 0;
                }
            }
        }

        return liveNeighbors;
    }

    void printCells() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                std::cout << cells[y][x].isAlive ? "*" : " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    GameOfLife game(10, 10);
    game.setCellAlive(1, 1, true);
    game.setCellAlive(2, 2, true);
    game.setCellAlive(3, 3, true);

    for (int i = 0; i < 5; i++) {
        std::cout << "Generation: " << i + 1 << "\n";
        game.printCells();
        game.nextGeneration();
    }

    return 0;
}