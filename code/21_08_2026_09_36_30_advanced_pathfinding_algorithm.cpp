#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Define the structure for a cell in the maze
struct Cell {
    int x, y;
    bool visited = false;
};

// Function to print the maze
void printMaze(const vector<vector<char>>& maze) {
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[0].size(); ++j) {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

// Function to find the shortest path using BFS
vector<vector<char>> bfsMazeSearch(vector<vector<char>>& maze, int startx, int starty, int endx, int endy) {
    // Create a queue for BFS and enqueue the starting cell
    queue<Cell> q;
    q.push({startx, starty});

    // Mark the starting cell as visited
    maze[startx][starty] = '#';

    // Directions to move in the maze (up, down, left, right)
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!q.empty()) {
        Cell cell = q.front();
        q.pop();

        // If the current cell is the destination, return the path
        if (cell.x == endx && cell.y == endy) {
            vector<vector<char>> path(maze.size(), vector<char>(maze[0].size()));
            int x = endx, y = endy;
            while (x != startx || y != starty) {
                path[x][y] = maze[x][y];
                for (int i = 0; i < 4; ++i) {
                    int newX = cell.x + dx[i], newY = cell.y + dy[i];
                    if (newX >= 0 && newX < maze.size() && newY >= 0 && newY < maze[0].size() &&
                        !maze[newX][newY] && !path[newX][newY]) {
                        x = newX; y = newY;
                        break;
                    }
                }
            }
            return path;
        }

        // Explore the neighbors of the current cell
        for (int i = 0; i < 4; ++i) {
            int newX = cell.x + dx[i], newY = cell.y + dy[i];
            if (newX >= 0 && newX < maze.size() && newY >= 0 && newY < maze[0].size() &&
                !maze[newX][newY] && !cell.visited) {
                q.push({newX, newY});
                cell.visited = true;
            }
        }
    }

    // If no path is found, return an empty vector
    vector<vector<char>> path(maze.size(), vector<char>(maze[0].size()));
    return path;
}

int main() {
    // Define the maze as a 2D array of characters
    vector<vector<char>> maze = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', '#'}
    };

    // Define the start and end points in the maze
    int startX = 1, startY = 2;
    int endX = 3, endY = 4;

    // Find the shortest path using BFS
    vector<vector<char>> path = bfsMazeSearch(maze, startX, startY, endX, endy);

    // Print the maze and the path
    cout << "Original Maze:" << endl;
    printMaze(maze);
    cout << "Shortest Path:" << endl;
    for (int i = 0; i < path.size(); ++i) {
        for (int j = 0; j < path[0].size(); ++j) {
            cout << path[i][j];
        }
        cout << endl;
    }

    return 0;
}