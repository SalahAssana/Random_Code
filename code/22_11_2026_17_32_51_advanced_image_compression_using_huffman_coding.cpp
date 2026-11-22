#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;

// Structure to represent Huffman node
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
};

// Function to build frequency table for given string
map<char, int> buildFrequencyTable(string str) {
    map<char, int> frequencyTable;
    for (char c : str) {
        if (frequencyTable.find(c) == frequencyTable.end()) {
            frequencyTable[c] = 1;
        } else {
            frequencyTable[c]++;
        }
    }
    return frequencyTable;
}

// Function to build Huffman tree using priority queue
Node* buildHuffmanTree(map<char, int> frequencyTable) {
    priority_queue<pair<int, char>> pq;
    for (auto it = frequencyTable.begin(); it != frequencyTable.end(); ++it) {
        pq.push({it->second, it->first});
    }

    Node* root = nullptr;
    while (!pq.empty()) {
        int f1 = pq.top().first;
        pq.pop();
        int f2 = pq.top().first;
        pq.pop();

        Node* newRoot = new Node();
        newRoot->freq = f1 + f2;
        newRoot->ch = '\0';
        newRoot->left = new Node();
        newRoot->right = new Node();
        newRoot->left->ch = pq.top().second;
        newRoot->right->ch = pq.top().second;

        if (pq.empty()) {
            root = newRoot;
        } else {
            pq.push({newRoot->freq, '\0'});
        }
    }

    return root;
}

// Function to traverse Huffman tree and generate Huffman codes
string generateHuffmanCodes(Node* root, string currentCode) {
    if (root == nullptr) {
        return "";
    }

    if (root->ch != '\0') {
        return currentCode;
    } else {
        return generateHuffmanCodes(root->left, currentCode + "0") +
               generateHuffmanCodes(root->right, currentCode + "1");
    }
}

// Function to compress image using Huffman coding
void compressImage(string filePath) {
    ifstream file(filePath);
    string imageStr;
    while (getline(file, imageStr)) {
        map<char, int> frequencyTable = buildFrequencyTable(imageStr);
        Node* root = buildHuffmanTree(frequencyTable);

        // Traverse the Huffman tree and generate Huffman codes
        map<char, string> huffmanCodes;
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* node = q.front();
            q.pop();

            if (node->ch != '\0') {
                huffmanCodes[node->ch] = generateHuffmanCodes(node, "");
            }

            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
        }

        // Compress the image using Huffman codes
        string compressedStr;
        for (char c : imageStr) {
            compressedStr += huffmanCodes[c];
        }

        cout << "Compressed image: " << compressedStr << endl;
    }
}

int main() {
    compressImage("image.txt");
    return 0;
}