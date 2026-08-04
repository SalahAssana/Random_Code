#include <iostream>
using namespace std;

// Define a struct for the tree node
struct Node {
    int data;
    Node* left;
    Node* right;
};

class BinarySearchTree {
public:
    // Constructor to initialize an empty tree
    BinarySearchTree() : root(nullptr) {}

    // Function to insert a new node with given value
    void insert(int value) {
        root = insertRecursive(root, value);
    }

    // Recursive function to insert a new node
    Node* insertRecursive(Node* current, int value) {
        if (current == nullptr) {
            return new Node{value, nullptr, nullptr};
        }
        
        if (value < current->data) {
            current->left = insertRecursive(current->left, value);
        } else if (value > current->data) {
            current->right = insertRecursive(current->right, value);
        }

        return current;
    }

    // Function to delete a node with given value
    void deleteNode(int value) {
        root = deleteRecursive(root, value);
    }

    // Recursive function to delete a node
    Node* deleteRecursive(Node* current, int value) {
        if (current == nullptr) {
            return nullptr;
        }
        
        if (value < current->data) {
            current->left = deleteRecursive(current->left, value);
        } else if (value > current->data) {
            current->right = deleteRecursive(current->right, value);
        } else {
            // Node found, perform deletion
            if (current->left == nullptr && current->right == nullptr) {
                // Leaf node, simply remove it
                delete current;
                return nullptr;
            }
            if (current->left == nullptr) {
                // Right child exists, move right child up
                Node* temp = current->right;
                delete current;
                return temp;
            }
            if (current->right == nullptr) {
                // Left child exists, move left child up
                Node* temp = current->left;
                delete current;
                return temp;
            }

            // Node has two children, find inorder successor and replace it with the node to be deleted
            Node* temp = minValueNode(current->right);
            current->data = temp->data;
            current->right = deleteRecursive(current->right, temp->data);
        }
        
        return current;
    }

    // Function to find the minimum value node in a given subtree
    Node* minValueNode(Node* current) {
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Function to perform inorder traversal and print values
    void traverse() {
        traverseRecursive(root);
    }

    // Recursive function to perform inorder traversal
    void traverseRecursive(Node* current) {
        if (current == nullptr) {
            return;
        }
        
        traverseRecursive(current->left);
        cout << current->data << " ";
        traverseRecursive(current->right);
    }

private:
    Node* root;
};

int main() {
    BinarySearchTree tree;

    // Insert some values
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    // Perform inorder traversal and print values
    cout << "Inorder Traversal: ";
    tree.traverse();
    cout << endl;

    // Delete some nodes
    tree.deleteNode(4);
    tree.deleteNode(2);

    // Perform inorder traversal again to show the updated tree
    cout << "Updated Inorder Traversal: ";
    tree.traverse();
    cout << endl;

    return 0;
}