#include <iostream>
using namespace std;

// Define the structure of a node in the binary tree
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Function to create a new node with given data
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the binary tree
void insertNode(Node*& root, int data) {
    if (root == NULL) {
        root = createNode(data);
        return;
    }

    if (data < root->data) {
        if (root->left == NULL) {
            root->left = createNode(data);
        } else {
            insertNode(root->left, data);
        }
    } else if (data > root->data) {
        if (root->right == NULL) {
            root->right = createNode(data);
        } else {
            insertNode(root->right, data);
        }
    }
}

// Function to search for a node in the binary tree
bool searchNode(Node* root, int data) {
    if (root == NULL) {
        return false;
    }

    if (data == root->data) {
        return true;
    }

    if (data < root->data) {
        return searchNode(root->left, data);
    } else {
        return searchNode(root->right, data);
    }
}

// Function to perform an in-order traversal of the binary tree
void inOrderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }

    inOrderTraversal(root->left);
    cout << root->data << " ";
    inOrderTraversal(root->right);
}

int main() {
    Node* root = NULL;

    // Insert nodes into the binary tree
    insertNode(root, 8);
    insertNode(root, 3);
    insertNode(root, 10);
    insertNode(root, 1);
    insertNode(root, 6);
    insertNode(root, 14);
    insertNode(root, 4);
    insertNode(root, 7);
    insertNode(root, 13);

    // Perform an in-order traversal of the binary tree
    cout << "In-order traversal: ";
    inOrderTraversal(root);
    cout << endl;

    // Search for a node in the binary tree
    int dataToSearch = 6;
    if (searchNode(root, dataToSearch)) {
        cout << "Found node with data " << dataToSearch << endl;
    } else {
        cout << "Node with data " << dataToSearch << " not found" << endl;
    }

    return 0;
}