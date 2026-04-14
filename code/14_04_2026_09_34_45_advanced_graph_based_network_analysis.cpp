#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits>

using namespace std;

class Graph {
public:
    map<int, vector<pair<int, int>>> adj;
    int V;

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int getCentrality(int node) {
        int centrality = 0;
        for (const auto& edge : adj[node]) {
            centrality += edge.second;
        }
        return centrality;
    }

    vector<int> communityDetection() {
        vector<int> communities(V, -1);
        queue<int> q;

        for (int i = 0; i < V; i++) {
            if (communities[i] == -1) {
                int node = i;
                while (node != -1) {
                    communities[node] = i;
                    node = -1;
                    for (const auto& edge : adj[node]) {
                        if (edge.second > 0) {
                            node = edge.first;
                            break;
                        }
                    }
                }
                q.push(i);
            }
        }

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (const auto& edge : adj[node]) {
                int neighbor = edge.first;
                if (communities[neighbor] == -1) {
                    communities[neighbor] = communities[node];
                } else if (communities[neighbor] != communities[node]) {
                    communities[neighbor] = node;
                    q.push(neighbor);
                }
            }
        }

        return communities;
    }

    int shortestPath(int source, int destination) {
        vector<int> distance(V, numeric_limits<int>::max());
        distance[source] = 0;

        queue<pair<int, int>> q;
        q.push({source, 0});

        while (!q.empty()) {
            pair<int, int> node = q.front();
            q.pop();

            for (const auto& edge : adj[node.first]) {
                if (edge.second < distance[edge.first] && distance[node.first] + edge.second < distance[edge.first]) {
                    distance[edge.first] = distance[node.first] + edge.second;
                    q.push({edge.first, distance[edge.first]});
                }
            }
        }

        return distance[destination];
    }
};

int main() {
    Graph graph;

    // Add edges
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 8);
    graph.addEdge(1, 2, 8);
    graph.addEdge(1, 3, 10);
    graph.addEdge(2, 3, 7);

    // Calculate centrality
    int centrality = graph.getCentrality(0);
    cout << "Centrality of node 0: " << centrality << endl;

    // Perform community detection
    vector<int> communities = graph.communityDetection();
    for (int i = 0; i < graph.V; i++) {
        cout << "Node " << i << ": Community " << communities[i] << endl;
    }

    // Find shortest path
    int shortestPathDistance = graph.shortestPath(0, 3);
    cout << "Shortest path distance from node 0 to node 3: " << shortestPathDistance << endl;

    return 0;
}