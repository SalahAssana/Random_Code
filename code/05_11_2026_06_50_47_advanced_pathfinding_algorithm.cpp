#include <iostream>
#include <queue>
#include <vector>
#include <limits>

using namespace std;

// Define a struct to represent a node in the grid
struct Node {
    int x, y; // coordinates of the node
    int distance; // shortest distance from the starting point
    bool visited; // whether the node has been visited
};

// Define a priority queue class for Dijkstra's algorithm
class PriorityQueue {
public:
    priority_queue<pair<int, Node>, vector<pair<int, Node>>, greater<pair<int, Node>>> pq;

    // Add an element to the priority queue
    void push(Node node) {
        pq.push({node.distance, node});
    }

    // Get the top element from the priority queue
    pair<int, Node> top() {
        return pq.top();
    }

    // Remove the top element from the priority queue
    void pop() {
        pq.pop();
    }
};

// Define a function to find the shortest path using Dijkstra's algorithm
vector<Node> dijkstra(int rows, int cols, vector<vector<int>>& grid, Node start, Node end) {
    // Create a 2D vector to store the distance from the starting point to each node
    vector<vector<int>> distances(rows, vector<int>(cols));

    // Initialize the priority queue and set the distance of the starting node to 0
    PriorityQueue pq;
    pq.push(start);
    start.distance = 0;

    while (!pq.empty()) {
        Node node = pq.top().second; // get the top node from the priority queue
        pq.pop();

        if (node.visited) continue; // skip visited nodes

        node.visited = true; // mark the node as visited

        // Check if we have reached the end node
        if (node.x == end.x && node.y == end.y) {
            break;
        }

        // Update distances of neighboring nodes
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (abs(dx) + abs(dy) != 1) continue; // skip diagonal neighbors

                int nx = node.x + dx;
                int ny = node.y + dy;

                if (nx < 0 || ny < 0 || nx >= rows || ny >= cols) continue; // out of bounds
                if (grid[nx][ny] == -1) continue; // obstacle

                int newDistance = distances[node.x][node.y] + 1;
                if (newDistance < distances[nx][ny]) {
                    distances[nx][ny] = newDistance;
                    pq.push(Node{nx, ny, newDistance, false});
                }
            }
        }
    }

    // Reconstruct the shortest path
    vector<Node> path;
    Node current = end;
    while (current.x != start.x || current.y != start.y) {
        path.push_back(current);
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (abs(dx) + abs(dy) != 1) continue;

                int nx = current.x + dx;
                int ny = current.y + dy;

                if (nx < 0 || ny < 0 || nx >= rows || ny >= cols) continue;
                if (grid[nx][ny] == -1) continue;

                if (distances[nx][ny] == distances[current.x][current.y] - 1) {
                    current = Node{nx, ny, distances[nx][ny], false};
                    break;
                }
            }
        }
    }

    // Return the shortest path
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int rows = 5; // number of rows in the grid
    int cols = 5; // number of columns in the grid

    vector<vector<int>> grid(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((i + j) % 2 == 1) {
                grid[i][j] = -1; // obstacle
            } else {
                grid[i][j] = 0; // empty cell
            }
        }
    }

    Node start{1, 1}; // starting point (x, y)
    Node end{3, 3}; // ending point (x, y)

    vector<Node> path = dijkstra(rows, cols, grid, start, end);

    cout << "Shortest Path: ";
    for (Node node : path) {
        cout << "(" << node.x << ", " << node.y << ") ";
    }
    cout << endl;

    return 0;
}