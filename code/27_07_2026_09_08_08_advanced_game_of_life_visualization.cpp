#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <random>

// Game of Life constants
const int WIDTH = 800;
const int HEIGHT = 600;
const int CELLSIZE = 2;

class Cell {
public:
    bool alive;
    sf::RectangleShape shape;
    sf::Vector2f position;

    Cell(int x, int y) : position(sf::Vector2f(x, y)) {
        alive = false;
        shape.setSize(sf::Vector2f(CELLSIZE, CELLSIZE));
        shape.setFillColor(alive ? sf::Color::Green : sf::Color::Black);
        shape.setPosition(position.x * CELLSIZE, position.y * CELLSIZE);
    }
};

class GameOfLife {
public:
    std::vector<Cell> cells;
    int width;
    int height;

    GameOfLife(int w, int h) : width(w), height(h) {
        for (int i = 0; i < w; ++i) {
            for (int j = 0; j < h; ++j) {
                Cell cell(i, j);
                cells.push_back(cell);
            }
        }
    }

    void update() {
        std::vector<Cell> newCells;
        for (Cell& cell : cells) {
            int livingNeighbors = countLivingNeighbors(cell.position.x, cell.position.y);
            if (cell.alive && (livingNeighbors < 2 || livingNeighbors > 3)) {
                cell.alive = false;
            } else if (!cell.alive && livingNeighbors == 3) {
                cell.alive = true;
            }
            newCells.push_back(cell);
        }
        cells = newCells;
    }

    int countLivingNeighbors(int x, int y) {
        int count = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if ((x + i >= 0 && x + i < width) &&
                    (y + j >= 0 && y + j < height)) {
                    count += cells[(y + j) * width + x + i].alive ? 1 : 0;
                }
            }
        }
        return count - (cellIsAlive(x, y) ? 1 : 0);
    }

    bool cellIsAlive(int x, int y) {
        return cells[y * width + x].alive;
    }

    void draw(sf::RenderWindow& window) {
        for (Cell& cell : cells) {
            if (cell.alive) {
                window.draw(cell.shape);
            }
        }
    }
};

int main() {
    sf::ContextSettings settings;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game of Life", sf::Style::Default, settings);

    GameOfLife gameOfLife(40, 20);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::bernoulli_distribution distribution(0.5);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                gameOfLife.update();
            }
        }

        window.clear();
        gameOfLife.draw(window);
        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}