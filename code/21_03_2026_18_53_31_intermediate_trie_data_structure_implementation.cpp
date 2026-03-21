#include <iostream>
#include <string>
using namespace std;

// TrieNode represents a node in the trie
struct TrieNode {
    char ch;
    bool isEndOfWord;
    struct TrieNode* children[26]; // 0-25 for lowercase alphabets
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
        root->isEndOfWord = false;
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c - 'a']) {
                node->children[c - 'a'] = new TrieNode();
            }
            node = node->children[c - 'a'];
        }
        node->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c - 'a']) return false;
            node = node->children[c - 'a'];
        }
        return node->isEndOfWord;
    }

    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (!node->children[c - 'a']) return false;
            node = node->children[c - 'a'];
        }
        return true;
    }

private:
    TrieNode* root;
};

int main() {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");

    cout << "Search apple: " << (trie.search("apple") ? "Found" : "Not found") << endl;
    cout << "Starts with app: " << (trie.startsWith("app") ? "True" : "False") << endl;

    return 0;
}