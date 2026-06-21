#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace std;

class Graph {
public:
    map<int, vector<pair<int, int>>> adjList;
    int numNodes;
};

void addEdge(Graph& graph, int u, int v) {
    graph.adjList[u].push_back({v, 1});
    graph.adjList[v].push_back({u, 1});
}

int communityDetection(Graph& graph) {
    vector<int> degrees(graph.numNodes);
    for (const auto& node : graph.adjList) {
        for (const auto& edge : node.second) {
            degrees[edge.first]++;
        }
    }

    int maxDegree = *max_element(degrees.begin(), degrees.end());
    int minDegree = *min_element(degrees.begin(), degrees.end());

    return maxDegree - minDegree;
}

void visualize(Graph& graph) {
    for (const auto& node : graph.adjList) {
        cout << node.first << ": ";
        for (const auto& edge : node.second) {
            cout << edge.first << " ";
        }
        cout << endl;
    }
}

int main() {
    Graph graph;
    graph.numNodes = 10;

    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);
    addEdge(graph, 5, 6);
    addEdge(graph, 6, 7);
    addEdge(graph, 7, 8);
    addEdge(graph, 8, 9);

    int community = communityDetection(graph);
    cout << "Community size: " << community << endl;

    visualize(graph);

    return 0;
}