#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <utility>

using namespace std;

// Define a struct to represent a cell in the grid
struct Cell {
    int x;
    int y;
    double g; // distance from start
    double h; // heuristic cost
    double f; // total cost (g+h)
};

// Define a priority queue using a heap
class PriorityQueue {
private:
    list<Cell> queue;

public:
    void push(const Cell& cell) {
        queue.push_front(cell);
    }

    Cell pop() {
        if(queue.empty()) {
            throw runtime_error("Queue is empty");
        }
        Cell front = queue.front();
        queue.pop_front();
        return front;
    }

    bool empty() {
        return queue.empty();
    }
};

// Define a class to represent the grid
class Grid {
private:
    vector<vector<Cell>> cells;

public:
    Grid(int width, int height) : cells(width, vector<Cell>(height)) {}

    void setStart(int x, int y) {
        if(x < 0 || x >= cells.size() || y < 0 || y >= cells[0].size()) {
            throw out_of_range("Invalid start coordinates");
        }
        cells[x][y].g = 0;
        cells[x][y].h = distance(x, y, cells.size() - 1, cells[0].size() - 1);
    }

    void setGoal(int x, int y) {
        if(x < 0 || x >= cells.size() || y < 0 || y >= cells[0].size()) {
            throw out_of_range("Invalid goal coordinates");
        }
        cells[x][y].h = distance(x, y, cells.size() - 1, cells[0].size() - 1);
    }

    Cell findPath(int start_x, int start_y, int goal_x, int goal_y) {
        PriorityQueue queue;
        setStart(start_x, start_y);
        setGoal(goal_x, goal_y);

        while(!queue.empty()) {
            Cell cell = queue.pop();
            if(cell.x == goal_x && cell.y == goal_y) {
                return cell;
            }

            for(int dx = -1; dx <= 1; ++dx) {
                for(int dy = -1; dy <= 1; ++dy) {
                    int new_x = cell.x + dx;
                    int new_y = cell.y + dy;
                    if(new_x >= 0 && new_x < cells.size() && new_y >= 0 && new_y < cells[0].size()) {
                        Cell neighbor = cells[new_x][new_y];
                        double cost = (dx == 0 || dy == 0) ? 1 : sqrt(dx * dx + dy * dy);
                        if(neighbor.g + cost < cell.f) {
                            neighbor.g += cost;
                            neighbor.f = neighbor.g + neighbor.h;
                            queue.push(neighbor);
                        }
                    }
                }
            }
        }

        throw runtime_error("No path found");
    }

private:
    double distance(int x1, int y1, int x2, int y2) {
        return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    }
};

int main() {
    Grid grid(10, 10);
    Cell path = grid.findPath(0, 0, 9, 9);
    cout << "Path found!" << endl;
    return 0;
}