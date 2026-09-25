#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Node {
    int x, y;
};

bool isValidMove(const vector<vector<int>>& maze, const Node& node) {
    return node.x >= 0 && node.x < maze.size() &&
           node.y >= 0 && node.y < maze[0].size();
}

int dijkstra(vector<vector<int>>& maze, Node start, Node end) {
    int rows = maze.size(), cols = maze[0].size();
    vector<vector<int>> dist(rows, vector<int>(cols, INF));
    priority_queue<pair<int, Node>, vector<pair<int, Node>>, greater<pair<int, Node>>> pq;

    pq.push({0, start});
    dist[start.x][start.y] = 0;

    while (!pq.empty()) {
        int cost = pq.top().first;
        Node node = pq.top().second;
        pq.pop();

        if (node == end) return cost;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int newX = node.x + dx, newY = node.y + dy;
                Node newNode = {newX, newY};

                if (isValidMove(maze, newNode)) {
                    int newCost = cost + (maze[newX][newY] == 0 ? 1 : INF);

                    if (newCost < dist[newX][newY]) {
                        dist[newX][newY] = newCost;
                        pq.push({newCost, newNode});
                    }
                }
            }
        }
    }

    return -1; // Not found
}

int main() {
    vector<vector<int>> maze = {
        {0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 1, 1},
        {0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0}
    };

    Node start = {0, 0}, end = {4, 5};
    int result = dijkstra(maze, start, end);

    cout << "Shortest distance from (" << start.x << ", " << start.y << ") to (" << end.x << ", " << end.y << "): " << result << endl;

    return 0;
}