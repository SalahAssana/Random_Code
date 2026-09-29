#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;

// Function to split a string into words
vector<string> split(const string& str) {
    vector<string> tokens;
    istringstream tokenStream(str);
    string token;
    while (getline(tokenStream, token, ' ')) {
        tokens.push_back(token);
    }
    return tokens;
}

// Trie node structure
struct TrieNode {
    map<char, TrieNode*> children;
    bool isWord;

    TrieNode() : isWord(false) {}
};

// Trie implementation
class Trie {
public:
    TrieNode* root;

    Trie() : root(new TrieNode()) {}

    void insert(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (!current->children.count(c)) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isWord = true;
    }

    vector<string> search(const string& query) {
        vector<string> results;
        TrieNode* current = root;
        for (char c : query) {
            if (!current->children.count(c)) {
                break;
            }
            current = current->children[c];
        }
        dfs(current, query, results);
        return results;
    }

private:
    void dfs(TrieNode* node, const string& query, vector<string>& results) {
        if (node->isWord) {
            int i = 0;
            for (; i < query.size(); ++i) {
                if (query[i] != node->children.begin()->first) {
                    break;
                }
            }
            if (i == query.size()) {
                string prefix = query.substr(0, i);
                results.push_back(prefix);
            }
        }
        for (const auto& pair : node->children) {
            dfs(pair.second, query.substr(i), results);
            ++i;
        }
    }
};

int main() {
    Trie trie;

    // Load the corpus of texts
    ifstream file("corpus.txt");
    string line;
    while (getline(file, line)) {
        for (const auto& word : split(line)) {
            trie.insert(word);
        }
    }

    // Perform a search query
    string query = "this is an example";
    vector<string> results = trie.search(query);

    // Print the search results
    cout << "Search results: ";
    for (const auto& result : results) {
        cout << result << " ";
    }
    cout << endl;

    return 0;
}