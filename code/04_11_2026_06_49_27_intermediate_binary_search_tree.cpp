#include <iostream>
using namespace std;

// Structure to represent a node in the binary search tree
struct Node {
    int data;
    Node* left;
    Node* right;
};

class BinarySearchTree {
public:
    // Constructor to initialize an empty tree
    BinarySearchTree() : root(nullptr) {}

    // Function to insert a new element into the tree
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

    // Function to delete an element from the tree
    void deleteNode(int value) {
        Node* nodeToDelete = root;
        Node* parentNode = nullptr;

        while (nodeToDelete != nullptr && nodeToDelete->data != value) {
            parentNode = nodeToDelete;
            if (value < nodeToDelete->data) {
                nodeToDelete = nodeToDelete->left;
            } else {
                nodeToDelete = nodeToDelete->right;
            }
        }

        if (nodeToDelete == nullptr) return;

        if (nodeToDelete->left == nullptr && nodeToDelete->right == nullptr) {
            // Node has no children, simply remove it
            if (parentNode != nullptr) {
                if (value < parentNode->data) {
                    parentNode->left = nullptr;
                } else {
                    parentNode->right = nullptr;
                }
            } else {
                root = nullptr;
            }
        } else if (nodeToDelete->left == nullptr || nodeToDelete->right == nullptr) {
            // Node has one child, replace it with the child
            Node* childNode = (nodeToDelete->left != nullptr) ? nodeToDelete->left : nodeToDelete->right;

            if (parentNode != nullptr) {
                if (value < parentNode->data) {
                    parentNode->left = childNode;
                } else {
                    parentNode->right = childNode;
                }
            } else {
                root = childNode;
            }

            delete nodeToDelete;
        } else {
            // Node has two children, find the replacement
            Node* replacement = nodeToDelete->right;

            while (replacement->left != nullptr) {
                replacement = replacement->left;
            }

            int valueToReplace = replacement->data;

            if (parentNode != nullptr) {
                if (value < parentNode->data) {
                    parentNode->left = replacement;
                } else {
                    parentNode->right = replacement;
                }
            } else {
                root = replacement;
            }

            // Replace the node with its smallest child
            Node* childNode = nodeToDelete->right;

            while (childNode != nullptr && childNode->left != nullptr) {
                childNode = childNode->left;
            }

            int valueToReplaceWith = childNode->data;

            if (parentNode != nullptr) {
                if (value < parentNode->data) {
                    parentNode->left = childNode;
                } else {
                    parentNode->right = childNode;
                }
            } else {
                root = childNode;
            }

            // Perform the actual deletion
            replacement->data = nodeToDelete->data;

            delete nodeToDelete;
        }
    }

    // Function to perform an in-order traversal of the tree
    void inOrderTraversal() {
        Node* current = root;
        while (true) {
            if (current == nullptr) break;

            if (current->left == nullptr) {
                cout << current->data << " ";
                current = current->right;
            } else {
                Node* nextNode = current->left;
                while (nextNode != nullptr && nextNode->left != nullptr) {
                    nextNode = nextNode->left;
                }

                if (current == root) {
                    root = nextNode;
                } else {
                    if (root->data < nextNode->data) {
                        root->right = nextNode;
                    } else {
                        root->left = nextNode;
                    }
                }

                cout << current->data << " ";
                current = current->right;
            }
        }
    }

private:
    Node* root;
};

int main() {
    BinarySearchTree tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    cout << "In-order traversal: ";
    tree.inOrderTraversal();
    cout << endl;

    tree.deleteNode(7);

    cout << "In-order traversal after deletion: ";
    tree.inOrderTraversal();
    cout << endl;

    return 0;
}