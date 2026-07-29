#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

class BinarySearchTree {
public:
    Node* root;

    // Constructor
    BinarySearchTree() : root(nullptr) {}

    // Insert a node with given value into the tree
    void insert(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->left = nullptr;
        newNode->right = nullptr;

        if (root == nullptr) {
            root = newNode;
        } else {
            Node* current = root;
            Node* parent = nullptr;

            while (true) {
                parent = current;
                if (value < current->data) {
                    current = current->left;
                    if (current == nullptr) {
                        parent->left = newNode;
                        break;
                    }
                } else {
                    current = current->right;
                    if (current == nullptr) {
                        parent->right = newNode;
                        break;
                    }
                }
            }
        }
    }

    // Delete a node with given value from the tree
    void deleteNode(int value) {
        root = deleteNodeRecursively(root, value);
    }

    Node* deleteNodeRecursively(Node* node, int value) {
        if (node == nullptr)
            return node;

        if (value < node->data) {
            node->left = deleteNodeRecursively(node->left, value);
            return node;
        }
        else if (value > node->data) {
            node->right = deleteNodeRecursively(node->right, value);
            return node;
        }

        // Node found
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;  // No child -> Simply delete this node
        }
        else if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;      // Only right child exists
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;      // Only left child exists
        }

        // Node has two children: Find the replacement node
        Node* temp = minValueNode(node->right);
        node->data = temp->data;
        node->right = deleteNodeRecursively(node->right, temp->data);

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;

        while (current && current->left)
            current = current->left;

        return current;
    }

    // Inorder traversal of the tree
    void inorderTraversal() {
        inorderTraversalRecursively(root);
    }

    void inorderTraversalRecursively(Node* node) {
        if (node == nullptr)
            return;

        inorderTraversalRecursively(node->left);
        cout << node->data << " ";
        inorderTraversalRecursively(node->right);
    }

    // Main function to test the code
    int main() {
        BinarySearchTree tree;
        tree.insert(8);
        tree.insert(3);
        tree.insert(10);
        tree.insert(1);
        tree.insert(6);
        tree.insert(14);
        tree.insert(4);
        tree.insert(7);
        tree.insert(13);

        cout << "Inorder Traversal of the inserted nodes: ";
        tree.inorderTraversal();
        cout << endl;

        tree.deleteNode(10);

        cout << "Inorder Traversal after deleting 10: ";
        tree.inorderTraversal();
        cout << endl;

        return 0;
    }