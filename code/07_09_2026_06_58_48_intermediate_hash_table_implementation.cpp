#include <iostream>
#include <vector>
#include <list>

using namespace std;

// Define a struct to represent a key-value pair
struct Pair {
    int key;
    string value;
};

class HashTable {
public:
    // Constructor to initialize the hash table with a given size
    HashTable(int size) : buckets(size), size(size), occupied(0) {}

    // Insert a new key-value pair into the hash table
    void insert(int key, const string& value) {
        int index = hashFunction(key);
        list<Pair>& bucket = buckets[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                // Update existing value
                it->value = value;
                return;
            }
        }

        // Insert new pair into the bucket
        Pair newPair{key, value};
        bucket.push_back(newPair);
        occupied++;
    }

    // Search for a key in the hash table and return its corresponding value
    string search(int key) {
        int index = hashFunction(key);

        for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            if (it->key == key) {
                return it->value;
            }
        }

        // Key not found in the bucket
        return "";
    }

    // Delete a key-value pair from the hash table
    void remove(int key) {
        int index = hashFunction(key);

        for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            if (it->key == key) {
                buckets[index].erase(it);
                occupied--;
                return;
            }
        }
    }

private:
    // Define a vector of lists to represent the hash table
    vector<list<Pair>> buckets;

    int size;  // Size of the hash table
    int occupied;  // Number of occupied slots in the hash table

    // Simple hash function using the key modulo the bucket size
    int hashFunction(int key) {
        return key % size;
    }
};

int main() {
    HashTable hashTable(10);

    // Insert some key-value pairs into the hash table
    hashTable.insert(1, "Apple");
    hashTable.insert(2, "Banana");
    hashTable.insert(3, "Cherry");
    hashTable.insert(11, "Orange");

    // Search for a value in the hash table
    cout << "Value of key 2: " << hashTable.search(2) << endl;

    // Remove a key-value pair from the hash table
    hashTable.remove(3);

    return 0;
}