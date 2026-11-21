#include <iostream>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <condition_variable>

// Node class to represent each node in the distributed hash table
class Node {
public:
    int id;
    std::vector<std::pair<int, int>> kvStore; // key-value store for this node

    Node(int id) : id(id) {}

    void addEntry(int key, int value) {
        kvStore.push_back({key, value});
    }

    bool getEntry(int key, int& value) {
        for (const auto& entry : kvStore) {
            if (entry.first == key) {
                value = entry.second;
                return true;
            }
        }
        return false;
    }
};

// Distributed Hash Table class
class DHT {
public:
    std::vector<Node> nodes; // list of all nodes in the distributed hash table

    DHT(int numNodes) : nodes(numNodes) {}

    void distributeEntries() {
        for (int i = 0; i < nodes.size(); i++) {
            int key = i;
            nodes[i % nodes.size()].addEntry(key, i);
        }
    }

    bool getEntry(int key, int& value) {
        // Use consistent hashing to determine which node this entry belongs to
        int targetNodeIndex = (key + 1) % nodes.size();
        if (!nodes[targetNodeIndex].getEntry(key, value)) {
            return false; // not found
        }
        return true;
    }
};

int main() {
    DHT dht(5); // create a distributed hash table with 5 nodes

    dht.distributeEntries(); // distribute entries to each node

    int key = 3;
    int value;
    if (dht.getEntry(key, value)) {
        std::cout << "Found entry for key " << key << ": " << value << std::endl;
    } else {
        std::cout << "Key not found." << std::endl;
    }

    return 0;
}