#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <map>

using namespace std;

struct Edge {
    int node;
    int weight;
};

class Graph {
public:
    map<int, vector<Edge>> adjList;
    void addEdge(int node1, int node2, int weight) {
        adjList[node1].push_back({node2, weight});
        adjList[node2].push_back({node1, weight});
    }
    vector<int> dijkstra(int startNode) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        map<int, int> distance;
        map<int, int> previous;
        for (auto& node : adjList) {
            distance[node.first] = numeric_limits<int>::max();
        }
        distance[startNode] = 0;
        pq.push({0, startNode});
        while (!pq.empty()) {
            auto current = pq.top(); pq.pop();
            int currentNode = current.second;
            if (distance[currentNode] < current.first) continue;
            for (auto& edge : adjList[currentNode]) {
                int neighbor = edge.node;
                int weight = edge.weight;
                int newDistance = distance[currentNode] + weight;
                if (newDistance < distance[neighbor]) {
                    distance[neighbor] = newDistance;
                    previous[neighbor] = currentNode;
                    pq.push({newDistance, neighbor});
                }
            }
        }
        vector<int> path;
        int currentNode = startNode;
        while (currentNode != -1) {
            path.push_back(currentNode);
            currentNode = previous[currentNode];
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    Graph graph;
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 6);
    vector<int> path = graph.dijkstra(0);
    cout << "Shortest path from node 0: ";
    for (auto& node : path) {
        cout << node << " ";
    }
    cout << endl;
    return 0;
}