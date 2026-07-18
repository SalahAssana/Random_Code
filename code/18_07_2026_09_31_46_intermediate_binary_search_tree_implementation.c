#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent nodes in the binary search tree
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node with given data
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new node with given data into the binary search tree
Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// Function to search for a node with given data in the binary search tree
Node* searchNode(Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return searchNode(root->left, data);
    }
    return searchNode(root->right, data);
}

// Function to delete a node with given data from the binary search tree
Node* deleteNode(Node** root, int data) {
    Node* temp = NULL;
    if (*root == NULL) {
        return *root;
    }

    if (data < (*root)->data) {
        (*root)->left = deleteNode(&((*root)->left), data);
    } else if (data > (*root)->data) {
        (*root)->right = deleteNode(&((*root)->right), data);
    } else {
        temp = *root;
        if ((*root)->left == NULL && (*root)->right == NULL) {
            *root = NULL;
        } else if ((*root)->left == NULL || (*root)->right == NULL) {
            *root = (*root)->left ? (*root)->left : (*root)->right;
        } else {
            temp = (*root)->right;
            (*root)->data = findMin((*root)->right);
            (*root)->right = deleteNode(&((*root)->right), (*root)->data);
        }
    }

    return temp;
}

// Function to find the minimum value in a subtree rooted at 'node'
int findMin(Node* node) {
    int minVal = node->data;
    while (node && node->left) {
        minVal = node->left->data;
        node = node->left;
    }
    return minVal;
}

// Function to print the binary search tree in a pre-order traversal
void printTree(Node* root, int level) {
    if (root != NULL) {
        for (int i = 0; i < level; i++)
            printf(" ");
        printf("%d\n", root->data);
        printTree(root->left, level + 1);
        printTree(root->right, level + 1);
    }
}

// Main function to test the binary search tree implementation
int main() {
    Node* root = NULL;

    // Insert nodes into the binary search tree
    root = insertNode(root, 8);
    root = insertNode(root, 3);
    root = insertNode(root, 10);
    root = insertNode(root, 1);
    root = insertNode(root, 6);
    root = insertNode(root, 14);
    root = insertNode(root, 4);
    root = insertNode(root, 7);
    root = insertNode(root, 13);

    // Print the binary search tree
    printf("Binary Search Tree:\n");
    printTree(root, 0);

    // Search for a node in the binary search tree
    Node* foundNode = searchNode(root, 10);
    if (foundNode) {
        printf("Found node with data %d\n", foundNode->data);
    } else {
        printf("Node not found\n");
    }

    // Delete a node from the binary search tree
    root = deleteNode(&root, 6);

    // Print the updated binary search tree
    printf("Updated Binary Search Tree:\n");
    printTree(root, 0);

    return 0;
}