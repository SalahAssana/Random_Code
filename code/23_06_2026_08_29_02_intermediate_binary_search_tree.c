#include <stdio.h>
#include <stdlib.h>

// Define the structure for a binary search tree node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node with given value
Node* newNode(int data) {
    Node* temp = (Node*) malloc(sizeof(Node));
    if (!temp) {
        printf("Memory error\n");
        return NULL;
    }
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert a new node with given value
void insert(Node** root, int data) {
    Node* newNode = newNode(data);
    if (*root == NULL) {
        *root = newNode;
    } else {
        Node* current = *root;
        while (1) {
            if (data < current->data) {
                if (!current->left) {
                    current->left = newNode;
                    return;
                }
                current = current->left;
            } else {
                if (!current->right) {
                    current->right = newNode;
                    return;
                }
                current = current->right;
            }
        }
    }
}

// Function to delete a node with given value
void deleteNode(Node** root, int data) {
    Node* temp = *root;
    Node* parent;
    if (temp == NULL) return;

    while (1) {
        parent = temp;
        if (data < temp->data) {
            temp = temp->left;
            if (temp == NULL) break;
        } else if (data > temp->data) {
            temp = temp->right;
            if (temp == NULL) break;
        } else {
            if (temp->left && temp->right) {
                Node* minNode = temp->right;
                int minValue = minNode->data;
                while (minNode->left) {
                    minNode = minNode->left;
                    minValue = minNode->data;
                }
                temp->data = minValue;
                deleteNode(&temp->right, minValue);
            } else if (!temp->left && !temp->right) {
                free(temp);
                *root = NULL;
            } else if (temp->left) {
                free(temp);
                *root = temp->left;
            } else {
                free(temp);
                *root = temp->right;
            }
            return;
        }
    }
}

// Function to search for a value in the tree
Node* search(Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return search(root->left, data);
    }

    return search(root->right, data);
}

// Function to print the tree in inorder
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;

    // Inserting values into the tree
    insert(&root, 5);
    insert(&root, 3);
    insert(&root, 7);
    insert(&root, 2);
    insert(&root, 4);
    insert(&root, 6);
    insert(&root, 8);

    // Printing the tree in inorder
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    // Deleting a node with value 3
    deleteNode(&root, 3);

    // Printing the tree again after deletion
    printf("After deletion, Inorder traversal: ");
    inorder(root);
    printf("\n");

    return 0;
}