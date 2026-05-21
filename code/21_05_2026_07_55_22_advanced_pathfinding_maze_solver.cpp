#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <functional>

using namespace std;

// Define a struct to represent a point in the maze
struct Point {
    int x, y;
};

// Define a struct to represent the maze and its cells
struct Cell {
    bool visited;
    int distance;
    Point parent;
};

class MazeSolver {
public:
    // Constructor to initialize the maze solver
    MazeSolver(int width, int height) : width(width), height(height) {}

    // Method to solve the maze using Dijkstra's algorithm
    vector<Point> solve(vector<vector<Cell>>& cells) {
        priority_queue<pair<int, Point>, vector<pair<int, Point>>, greater<pair<int, Point>>> queue;
        vector<Point> path;

        // Find the starting point (assuming it's the top-left cell)
        int startX = 0, startY = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (!cells[i][j].visited) {
                    startX = j;
                    startY = i;
                    break;
                }
            }
            if (!cells[startY][startX].visited) break;
        }

        // Mark the starting cell as visited and set its distance to 0
        cells[startY][startX].visited = true;
        cells[startY][startX].distance = 0;

        // Enqueue the starting cell with a distance of 0
        queue.push({0, {startX, startY}});

        while (!queue.empty()) {
            pair<int, Point> current = queue.top();
            queue.pop();

            // Reconstruct the path by following the parent pointers
            int x = current.second.x;
            int y = current.second.y;
            while (true) {
                if (x == startX && y == startY) break;

                cells[y][x].visited = true;
                Point parent = cells[y][x].parent;
                x = parent.x;
                y = parent.y;
            }

            // Backtrack and construct the path
            vector<Point> backtrackingPath;
            while (true) {
                backtrackingPath.push_back({x, y});
                if (x == startX && y == startY) break;

                Point parent = cells[y][x].parent;
                x = parent.x;
                y = parent.y;
            }

            // Reverse the path and return it
            reverse(backtrackingPath.begin(), backtrackingPath.end());
            return backtrackingPath;
        }

        // If no path is found, return an empty vector
        return {};
    }

private:
    int width, height;
};

// Function to generate a random maze
vector<vector<Cell>> generateMaze(int width, int height) {
    vector<vector<Cell>> cells(height, vector<Cell>(width));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cells[i][j].visited = false;
            cells[i][j].distance = numeric_limits<int>::max();
            cells[i][j].parent = {-1, -1};
        }
    }

    // Add some random walls
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (rand() % 2 == 1) cells[i][j].visited = true;
        }
    }

    return cells;
}

int main() {
    srand(time(0));

    // Generate a random maze
    int width = 20, height = 15;
    vector<vector<Cell>> cells = generateMaze(width, height);

    // Solve the maze using Dijkstra's algorithm
    MazeSolver solver(width, height);
    vector<Point> path = solver.solve(cells);

    // Display the solution graphically (assuming you have a GUI library)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (path.size() > 1 && pair(first(path), Point(j, i)) in path) cout << "* ";
            else cout << "  ";
        }
        cout << endl;
    }

    return 0;
}