#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int TABLE_SIZE = 10;
class HashTable {
public:
    struct Entry {
        string key;
        int value;
    };
    vector<Entry> table[TABLE_SIZE];

    void insert(const string& key, int value) {
        int hashValue = hashCode(key);
        for (Entry& entry : table[hashValue]) {
            if (entry.key == key) {
                // Update the existing value
                entry.value = value;
                return;
            }
        }
        table[hashValue].push_back({key, value});
    }

    bool search(const string& key) {
        int hashValue = hashCode(key);
        for (const auto& entry : table[hashValue]) {
            if (entry.key == key) {
                return true;
            }
        }
        return false;
    }

    void remove(const string& key) {
        int hashValue = hashCode(key);
        for (auto it = table[hashValue].begin(); it != table[hashValue].end();) {
            if (it->key == key) {
                it = table[hashValue].erase(it);
                return;
            }
            ++it;
        }
    }

private:
    int hashCode(const string& str) {
        int hash = 0;
        for (char c : str) {
            hash += (int)c;
        }
        return hash % TABLE_SIZE;
    }
};

int main() {
    HashTable ht;

    ht.insert("apple", 5);
    ht.insert("banana", 10);
    ht.insert("orange", 15);

    cout << "Searching for 'apple': " << (ht.search("apple") ? "Found" : "Not found") << endl;
    cout << "Searching for 'grape': " << (ht.search("grape") ? "Found" : "Not found") << endl;

    ht.remove("banana");

    cout << "Searching for 'banana': " << (ht.search("banana") ? "Found" : "Not found") << endl;
    return 0;
}