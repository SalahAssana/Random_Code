#include <iostream>
#include <vector>
#include <map>
#include <limits>

using namespace std;

// Structure to represent a graph
struct Graph {
    int V; // Number of vertices
    vector<vector<int>> adjList; // Adjacency list representation
};

// Function to perform DFS traversal and color the graph
void dfs(int v, int color[], Graph& g) {
    for (int i = 0; i < g.adjList[v].size(); i++) {
        int neighbor = g.adjList[v][i];
        if (color[neighbor] == -1) {
            // If the neighbor is not colored yet
            color[neighbor] = 1 - color[v]; // Assign the opposite color
            dfs(neighbor, color, g);
        }
    }
}

// Function to implement the greedy graph coloring algorithm
vector<int> greedyColoring(Graph& g) {
    int V = g.V; // Get the number of vertices
    vector<int> color(V, -1); // Initialize the color array

    for (int v = 0; v < V; v++) {
        if (color[v] == -1) {
            // If the vertex is not colored yet
            dfs(v, color, g);
        }
    }

    return color;
}

// Function to print the coloring result
void printColoring(vector<int>& color, int V) {
    cout << "Coloring Result: ";
    for (int v = 0; v < V; v++) {
        cout << color[v] << " ";
    }
    cout << endl;
}

// Main function
int main() {
    // Example graph data
    Graph g;
    g.V = 5;
    vector<vector<int>> adjList = {{1, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 3}};
    for (int i = 0; i < 5; i++) {
        g.adjList.push_back(adjList[i]);
    }

    // Perform greedy graph coloring
    vector<int> color = greedyColoring(g);

    // Print the coloring result
    printColoring(color, g.V);

    return 0;
}