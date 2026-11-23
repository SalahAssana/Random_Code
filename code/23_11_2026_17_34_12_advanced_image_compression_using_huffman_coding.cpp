#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct Node {
    char symbol;
    int frequency;
    Node* left;
    Node* right;
};

// Priority queue for Huffman coding
priority_queue<Node*, vector<Node*>, function<bool(const Node*, const Node*)> q("greater");

void buildHuffmanTree(ifstream& file, map<char, int>& freq) {
    char ch;
    while (file.get(ch)) {
        freq[ch]++;
    }
}

Node* createLeaf(char symbol, int frequency) {
    Node* leaf = new Node();
    leaf->symbol = symbol;
    leaf->frequency = frequency;
    leaf->left = nullptr;
    leaf->right = nullptr;
    return leaf;
}

Node* mergeNodes(Node* left, Node* right) {
    Node* node = new Node();
    node->symbol = '\0';
    node->frequency = left->frequency + right->frequency;
    node->left = left;
    node->right = right;
    q.push(node);
    return node;
}

Node* buildHuffmanTree(map<char, int>& freq) {
    for (auto& pair : freq) {
        q.push(createLeaf(pair.first, pair.second));
    }
    
    while (q.size() > 1) {
        Node* left = q.top(); q.pop();
        Node* right = q.top(); q.pop();
        q.push(mergeNodes(left, right));
    }

    return q.top();
}

void buildHuffmanCode(Node* root, map<char, string>& codeMap) {
    if (root->left == nullptr && root->right == nullptr) {
        codeMap[root->symbol] = "";
    } else {
        if (root->left != nullptr) {
            codeMap[root->symbol] += "0";
            buildHuffmanCode(root->left, codeMap);
        }
        if (root->right != nullptr) {
            codeMap[root->symbol] += "1";
            buildHuffmanCode(root->right, codeMap);
        }
    }
}

void compressImage(ifstream& file, ofstream& compressedFile) {
    map<char, int> freq;
    buildHuffmanTree(file, freq);

    Node* root = buildHuffmanTree(freq);
    map<char, string> codeMap;
    buildHuffmanCode(root, codeMap);

    char ch;
    while (file.get(ch)) {
        for (auto& pair : codeMap) {
            if (pair.first == ch) {
                compressedFile << pair.second;
                break;
            }
        }
    }

    file.close();
    compressedFile.close();
}

int main() {
    ifstream file("image.txt", ios::binary);
    ofstream compressedFile("compressed.txt", ios::binary);

    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return 1;
    }

    if (!compressedFile.is_open()) {
        cout << "Error creating compressed file." << endl;
        return 1;
    }

    compressImage(file, compressedFile);

    return 0;
}