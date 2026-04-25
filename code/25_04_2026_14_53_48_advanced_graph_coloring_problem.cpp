#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Graph represented as an adjacency list
struct Graph {
    int V;
    vector<vector<int>> adjList;

    Graph(int V) : V(V), adjList(V) {}
};

class ColorGraph {
public:
    // Function to check if the graph is colored properly
    bool isValidColoring(vector<int> &coloring, Graph &graph) {
        for (int i = 0; i < graph.V; ++i) {
            for (int j : graph.adjList[i]) {
                if (coloring[i] == coloring[j])
                    return false;
            }
        }
        return true;
    }

    // Function to perform depth-first search and backtracking
    bool colorGraph(vector<int> &coloring, Graph &graph, int currentColor) {
        for (int i = 0; i < graph.V; ++i) {
            if (!isAvailable(graph.adjList[i], coloring, currentColor)) {
                return false;
            }
        }
        return true;
    }

    // Helper function to check availability of a color
    bool isAvailable(vector<int> &neighbors, vector<int> &coloring, int targetColor) {
        for (int i : neighbors) {
            if (coloring[i] == targetColor)
                return false;
        }
        return true;
    }

    // Main function to solve the graph coloring problem
    void solve(Graph &graph) {
        vector<int> coloring(graph.V);
        int currentColor = 1;

        while (true) {
            bool colored = colorGraph(coloring, graph, currentColor);

            if (!colored)
                return;  // Backtrack

            for (int i = 0; i < graph.V; ++i)
                coloring[i] = currentColor;

            currentColor++;
        }
    }
};

int main() {
    Graph graph(5);
    graph.adjList.push_back({1, 2});
    graph.adjList.push_back({0, 3});
    graph.adjList.push_back({0, 4});
    graph.adjList.push_back({1, 4});
    graph.adjList.push_back({3});

    ColorGraph colorGraph;
    vector<int> coloring;

    colorGraph.solve(graph);

    if (coloring.size() == graph.V) {
        cout << "Coloring: ";
        for (int i = 0; i < coloring.size(); ++i)
            cout << coloring[i] << " ";
        cout << endl;
    } else
        cout << "No solution found." << endl;

    return 0;
}