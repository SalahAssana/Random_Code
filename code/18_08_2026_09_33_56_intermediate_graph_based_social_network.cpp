#include <iostream>
#include <list>
#include <map>
#include <string>

using namespace std;

// Node structure to represent a person in the social network
struct Node {
    int id;
    list<int> friends; // list of friend IDs
};

// Graph class to manage the social network
class Graph {
public:
    map<int, Node*> nodes; // map of node IDs to their corresponding nodes

    // Add a new node to the graph
    void addNode(int id) {
        Node* newNode = new Node();
        newNode->id = id;
        nodes[id] = newNode;
    }

    // Connect two nodes (add them as friends)
    void connectNodes(int node1, int node2) {
        if (nodes.find(node1) != nodes.end() && nodes.find(node2) != nodes.end()) {
            Node* node1Data = nodes[node1];
            Node* node2Data = nodes[node2];

            // Add node2 as a friend of node1
            node1Data->friends.push_back(node2);

            // Add node1 as a friend of node2
            node2Data->friends.push_back(node1);
        }
    }

    // Print the social network (adjacency list)
    void printNetwork() {
        for (auto& pair : nodes) {
            cout << "Node " << pair.first << ": ";
            for (int friendId : pair.second->friends) {
                cout << friendId << " ";
            }
            cout << endl;
        }
    }

    // Find the shortest path between two nodes
    void findShortestPath(int start, int end) {
        if (nodes.find(start) == nodes.end() || nodes.find(end) == nodes.end()) {
            cout << "Error: Nodes not found." << endl;
            return;
        }

        // Perform BFS to find the shortest path
        queue<pair<int, int>> q;
        map<int, int> distance; // store the shortest distance from start node
        map<int, int> previous; // store the previous node in the shortest path

        distance[start] = 0;
        previous[start] = -1;

        q.push({start, 0});

        while (!q.empty()) {
            int currentNodeId = q.front().first;
            int currentDistance = q.front().second;
            q.pop();

            if (currentNodeId == end) {
                // Reconstruct the shortest path
                cout << "Shortest path: ";
                int temp = end;
                while (temp != -1) {
                    cout << temp << " ";
                    temp = previous[temp];
                }
                cout << endl;
                return;
            }

            for (int friendId : nodes[currentNodeId]->friends) {
                if (distance.find(friendId) == distance.end() || currentDistance + 1 < distance[friendId]) {
                    distance[friendId] = currentDistance + 1;
                    previous[friendId] = currentNodeId;
                    q.push({friendId, currentDistance + 1});
                }
            }
        }

        cout << "Error: No path found." << endl;
    }
};

int main() {
    Graph graph;

    // Add nodes
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);

    // Connect nodes
    graph.connectNodes(1, 2);
    graph.connectNodes(2, 3);
    graph.connectNodes(1, 3);

    // Print the social network
    cout << "Social Network:" << endl;
    graph.printNetwork();

    // Find the shortest path between two nodes
    cout << "Shortest Path from Node 1 to Node 3:" << endl;
    graph.findShortestPath(1, 3);

    return 0;
}