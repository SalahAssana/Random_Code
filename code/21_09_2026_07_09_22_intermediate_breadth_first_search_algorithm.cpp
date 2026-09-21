#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Define a graph node
struct GraphNode {
    int value;
    vector<GraphNode*> neighbors;
};

// Function to perform BFS traversal
void breadthFirstSearch(GraphNode* start, const string& goal) {
    queue<GraphNode*> q;
    q.push(start);

    set<string> visited;
    visited.insert(to_string(start->value));

    while (!q.empty()) {
        GraphNode* current = q.front();
        q.pop();

        if (current->value == stoi(goal)) {
            cout << "Goal node found: " << goal << endl;
            return;
        }

        for (GraphNode* neighbor : current->neighbors) {
            string neighborStr = to_string(neighbor->value);
            if (visited.find(neighborStr) == visited.end()) {
                q.push(neighbor);
                visited.insert(neighborStr);
            }
        }
    }

    cout << "Goal node not found." << endl;
}

int main() {
    // Create a sample graph
    vector<GraphNode*> graphNodes = {
        new GraphNode{1},
        new GraphNode{2},
        new GraphNode{3},
        new GraphNode{4},
        new GraphNode{5}
    };

    // Connect nodes as an adjacency list
    graphNodes[0]->neighbors.push_back(graphNodes[1]);
    graphNodes[0]->neighbors.push_back(graphNodes[2]);
    graphNodes[1]->neighbors.push_back(graphNodes[3]);
    graphNodes[2]->neighbors.push_back(graphNodes[4]);

    // Perform BFS traversal starting from node 1 and searching for node 5
    breadthFirstSearch(graphNodes[0], "5");

    return 0;
}