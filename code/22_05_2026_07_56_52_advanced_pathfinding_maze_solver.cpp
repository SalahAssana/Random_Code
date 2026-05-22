#include <queue>
#include <unordered_map>
#include <vector>
#include <utility>

using namespace std;

// Node class to represent each cell in the maze
class Node {
public:
    int x, y; // coordinates of the node
    int g, h, f; // cost function values (g: distance from start, h: heuristic, f: total cost)
};

// Heuristic function to estimate the distance from a given node to the goal
int heuristic(Node& node) {
    return abs(node.x - 10) + abs(node.y - 10); // Manhattan distance for this maze
}

// A* algorithm to find the shortest path in the maze
vector<pair<int, int>> aStar(vector<vector<bool>>& maze, pair<int, int> start, pair<int, int> goal) {
    priority_queue<Node*, vector<Node*>, function<bool(const Node&, const Node&)>> pq([=](Node& a, Node& b) { return a.f > b.f; });
    unordered_map<pair<int, int>, Node*> cameFrom;
    Node* startNode = new Node{start.first, start.second, 0, heuristic({start.first, start.second}), 0};
    pq.push(startNode);
    
    while (!pq.empty()) {
        Node* currentNode = pq.top();
        pq.pop();
        
        if (currentNode->x == goal.first && currentNode->y == goal.second) {
            vector<pair<int, int>> path;
            while (currentNode != startNode) {
                cameFrom[make_pair(currentNode->x, currentNode->y)] = currentNode;
                currentNode = cameFrom[make_pair(currentNode->x, currentNode->y)];
            }
            while (startNode != nullptr) {
                path.emplace_back(startNode->x, startNode->y);
                startNode = cameFrom[make_pair(startNode->x, startNode->y)];
            }
            reverse(path.begin(), path.end());
            return path;
        }
        
        for (int dx : {-1, 0, 1}) {
            int newX = currentNode->x + dx;
            for (int dy : {-1, 0, 1}) {
                if (abs(dx) == 1 && abs(dy) == 1) continue; // skip diagonals
                int newY = currentNode->y + dy;
                
                if (newX < 0 || newX >= maze.size() || newY < 0 || newY >= maze[0].size()) continue; // out of bounds
                if (!maze[newX][newY]) continue; // blocked cell
                
                Node* newNode = new Node{newX, newY, currentNode->g + 1, heuristic({newX, newY}), currentNode->g + 1 + heuristic({newX, newY})};
                
                if (cameFrom.find(make_pair(newNode->x, newNode->y)) == cameFrom.end()) {
                    pq.push(newNode);
                    cameFrom[make_pair(newNode->x, newNode->y)] = newNode;
                }
            }
        }
    }
    
    return vector<pair<int, int>>{}; // no path found
}

int main() {
    vector<vector<bool>> maze(11, vector<bool>(11)); // 10x10 maze with some walls
    
    for (int i = 1; i < 10; ++i) {
        for (int j = 1; j < 10; ++j) {
            if ((i + j) % 2 == 0) { // alternate walls
                maze[i][j] = false;
            } else {
                maze[i][j] = true;
            }
        }
    }
    
    pair<int, int> start(1, 1), goal(9, 9);
    vector<pair<int, int>> path = aStar(maze, start, goal);
    
    if (!path.empty()) {
        cout << "Path found: ";
        for (pair<int, int>& point : path) {
            cout << "(" << point.first << ", " << point.second << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found." << endl;
    }
    
    return 0;
}
