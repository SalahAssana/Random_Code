#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the BST
typedef struct {
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
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the BST
Node* insertNode(Node* root, int data) {
    if (!root) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// Function to search for a node in the BST
int* searchNode(Node* root, int data) {
    if (!root || root->data == data) {
        return &root->data; // Return the data of the found node
    }

    if (data < root->data) {
        return searchNode(root->left, data);
    } else {
        return searchNode(root->right, data);
    }
}

// Function to delete a node from the BST
Node* deleteNode(Node* root, int data) {
    if (!root) {
        return root;
    }

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left && root->right) {
            int minVal = findMinValue(root->right);
            root->data = minVal;
            root->right = deleteNode(root->right, minVal);
        } else if (root->left) {
            return root->left;
        } else if (root->right) {
            return root->right;
        } else {
            free(root);
            return NULL;
        }
    }
    return root;
}

// Function to find the minimum value in a BST
int findMinValue(Node* root) {
    while (root && root->left) {
        root = root->left;
    }
    return root->data;
}

// Function to print the inorder traversal of the BST
void printInorderTraversal(Node* root) {
    if (!root) {
        return;
    }

    printInorderTraversal(root->left);
    printf("%d ", root->data);
    printInorderTraversal(root->right);
}

int main() {
    Node* root = NULL;

    // Insert nodes into the BST
    root = insertNode(root, 50);
    root = insertNode(root, 30);
    root = insertNode(root, 20);
    root = insertNode(root, 40);
    root = insertNode(root, 70);
    root = insertNode(root, 60);
    root = insertNode(root, 80);

    // Print the inorder traversal of the BST
    printf("Inorder Traversal: ");
    printInorderTraversal(root);
    printf("\n");

    // Search for a node in the BST
    int* searchData = searchNode(root, 40);
    if (*searchData != -1) {
        printf("Found %d\n", *searchData);
    } else {
        printf("Not found\n");
    }

    // Delete a node from the BST
    root = deleteNode(root, 20);

    // Print the inorder traversal of the BST after deletion
    printf("Inorder Traversal after deletion: ");
    printInorderTraversal(root);
    printf("\n");

    return 0;
}