#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

const int TABLE_SIZE = 10; // Size of hash table (must be prime number)

struct HashNode {
    std::string key;
    std::string value;

    bool operator==(const HashNode& other) const {
        return key == other.key;
    }
};

class HashTable {
public:
    HashTable() : table_(new std::vector<HashNode>[TABLE_SIZE]) {}

    ~HashTable() {
        delete[] table_;
    }

    void insert(const std::string& key, const std::string& value) {
        int index = hash(key);
        for (auto& node : table_[index]) {
            if (node.key == key) {
                // Key already exists, update the value
                node.value = value;
                return;
            }
        }
        table_[index].push_back({key, value});
    }

    bool search(const std::string& key) const {
        int index = hash(key);
        for (const auto& node : table_[index]) {
            if (node.key == key) {
                return true;
            }
        }
        return false;
    }

    void remove(const std::string& key) {
        int index = hash(key);
        for (auto it = table_[index].begin(); it != table_[index].end();) {
            if (it->key == key) {
                it = table_[index].erase(it);
                return;
            }
            ++it;
        }
    }

private:
    int hash(const std::string& key) const {
        int sum = 0;
        for (char c : key) {
            sum += static_cast<int>(c);
        }
        return sum % TABLE_SIZE;
    }

    std::vector<HashNode>* table_;
};

int main() {
    HashTable hashTable;

    hashTable.insert("apple", "red");
    hashTable.insert("banana", "yellow");

    if (hashTable.search("apple")) {
        std::cout << "Apple is red." << std::endl;
    } else {
        std::cout << "Apple not found." << std::endl;
    }

    hashTable.remove("apple");

    if (!hashTable.search("apple")) {
        std::cout << "Apple removed successfully." << std::endl;
    } else {
        std::cout << "Apple still exists." << std::endl;
    }

    return 0;
}