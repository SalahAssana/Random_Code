#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int MAX_WIDTH = 21;
const int MAX_HEIGHT = 11;
const int START_X = 1;
const int START_Y = 1;
const int END_X = MAX_WIDTH - 2;
const int END_Y = MAX_HEIGHT - 2;

struct Cell {
    bool visited;
    int x, y;
};

vector<vector<Cell>> map(MAX_HEIGHT, vector<Cell>(MAX_WIDTH));

void printMap() {
    for (int i = 0; i < MAX_HEIGHT; ++i) {
        for (int j = 0; j < MAX_WIDTH; ++j) {
            if (!map[i][j].visited) cout << '#';
            else cout << ' ';
        }
        cout << endl;
    }
}

bool isPath(int x, int y) {
    return map[x][y].visited;
}

void markPath(int x, int y) {
    map[x][y].visited = true;
}

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

bool isDestination(int x, int y) {
    return x == END_X && y == END_Y;
}

void pathfinder(int startX, int startY, int endX, int endY) {
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> queue;

    map[startX][startY].visited = true;
    queue.push({0, {startX, startY}});

    while (!queue.empty()) {
        auto [dist, {x, y}] = queue.top();
        queue.pop();

        if (isDestination(x, y)) {
            cout << "Path found!" << endl;
            return;
        }

        for (int dx : {-1, 0, 1}) {
            for (int dy : {-1, 0, 1}) {
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && nx < MAX_WIDTH && ny >= 0 && ny < MAX_HEIGHT) {
                    if (!isPath(nx, ny)) {
                        queue.push({dist + heuristic(startX, startY, nx, ny), {nx, ny}});
                        markPath(nx, ny);
                    }
                }
            }
        }
    }

    cout << "No path found." << endl;
}

int main() {
    for (int i = 0; i < MAX_HEIGHT; ++i) {
        for (int j = 0; j < MAX_WIDTH; ++j) {
            map[i][j].visited = false;
        }
    }

    pathfinder(START_X, START_Y, END_X, END_Y);

    return 0;
}
