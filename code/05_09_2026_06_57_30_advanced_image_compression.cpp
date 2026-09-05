#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
};

void printCodes(Node* root, string str) {
    if (!root)
        return;
    if (root->ch != '\0') {
        cout << root->ch << ": " << str << endl;
    }
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

Node* constructTree(int freq[], int size) {
    Node *root = NULL;
    priority_queue<Node*> q;
    for (int i = 0; i < size; i++) {
        Node *temp = new Node();
        temp->ch = '\0';
        temp->freq = freq[i];
        temp->left = temp->right = NULL;
        q.push(temp);
    }
    
    while (q.size() > 1) {
        Node* left = q.top(); q.pop();
        Node* right = q.top(); q.pop();
        
        Node *temp = new Node();
        temp->ch = '\0';
        temp->freq = left->freq + right->freq;
        temp->left = left;
        temp->right = right;
        q.push(temp);
    }
    
    root = q.top(); q.pop();
    return root;
}

void compressImage(const char *filename) {
    ifstream file(filename, ios::binary);
    vector<char> buffer((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));

    int freq[256] = {0};
    for (char c : buffer)
        freq[c]++;
    
    Node* root = constructTree(freq, 256);
    
    map<char, string> huffmanCode;
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        Node* node = q.front(); q.pop();
        
        if (node->left && node->right) {
            string leftCode = huffmanCode[node->left->ch];
            string rightCode = huffmanCode[node->right->ch];
            
            huffmanCode[node->ch] = leftCode.length() == 0 ? "0" : leftCode + "0";
            huffmanCode[node->ch].append(rightCode);
        } else {
            if (node->left)
                huffmanCode[node->ch] = huffmanCode[node->left->ch];
            else
                huffmanCode[node->ch] = "";
        }
    }
    
    ofstream compressedFile("compressed_" + filename, ios::binary);
    
    for (char c : buffer) {
        compressedFile.write((huffmanCode[c].c_str()), huffmanCode[c].size());
        compressedFile.write("\0", 1);
    }
}

int main() {
    compressImage("image.jpg");
    return 0;
}