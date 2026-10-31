#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Structure for the maze cell
struct Cell {
    bool visited;
    int x, y; // coordinates of the cell
};

class MazeSolver {
public:
    vector<vector<Cell>> solveMaze(vector<vector<char>>& maze) {
        int rows = maze.size();
        int cols = maze[0].size();

        vector<vector<Cell>> solvedMaze(rows, vector<Cell>(cols));
        stack<Cell> path;

        // Start from the top-left cell
        Cell startCell;
        startCell.x = 0;
        startCell.y = 0;
        startCell.visited = false;
        path.push(startCell);

        while (!path.empty()) {
            Cell currentCell = path.top();
            path.pop();

            if (currentCell.visited) continue;

            // If we reached the end, return
            if (currentCell.x == rows - 1 && currentCell.y == cols - 1)
                break;

            // Explore neighbors
            vector<Cell> neighbors;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int newX = currentCell.x + dx;
                    int newY = currentCell.y + dy;

                    if (newX >= 0 && newX < rows &&
                        newY >= 0 && newY < cols &&
                        maze[newX][newY] != '#') {

                        Cell neighbor;
                        neighbor.x = newX;
                        neighbor.y = newY;
                        neighbor.visited = false;
                        neighbors.push_back(neighbor);
                    }
                }
            }

            // Perform depth-first search
            for (Cell& neighbor : neighbors) {
                if (!solvedMaze[neighbor.x][neighbor.y].visited) {
                    path.push(neighbor);
                    solvedMaze[neighbor.x][neighbor.y] = currentCell;
                } else if (neighbor.x == rows - 1 && neighbor.y == cols - 1)
                    break; // Found the end, return
            }
        }

        return solvedMaze;
    }
};

int main() {
    MazeSolver solver;

    vector<vector<char>> maze = {
        {'#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#'},
        {'#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#'}
    };

    vector<vector<Cell>> solvedMaze = solver.solveMaze(maze);

    // Print the solved maze
    for (const auto& row : solvedMaze) {
        for (const auto& cell : row) {
            if (!cell.visited)
                cout << '#';
            else
                cout << ' ';
        }
        cout << '\n';
    }

    return 0;
}