#include <stdio.h>
#include <stdlib.h>

// Define a structure for Tree Node
typedef struct {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create new TreeNode
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        printf("Memory not allocated.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to perform DFS traversal
void dfsTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    printf("%d ", root->data);

    // Traverse left subtree
    dfsTraversal(root->left);

    // Traverse right subtree
    dfsTraversal(root->right);
}

// Function to perform BFS traversal
void bfsTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    int queueSize = 1;
    TreeNode* temp;
    int i;

    printf("%d ", root->data);

    // Create a queue for BFS
    TreeNode** queue = (TreeNode**)malloc(sizeof(TreeNode*) * queueSize);
    queue[0] = root;

    while (queueSize > 0) {
        temp = queue[0];
        for (i = 0; i < queueSize; i++) {
            printf("%d ", temp->data);

            // Dequeue an element
            temp = queue[i];

            // Enqueue left child
            if (temp->left != NULL) {
                queue[queueSize] = temp->left;
                queueSize++;
            }

            // Enqueue right child
            if (temp->right != NULL) {
                queue[queueSize] = temp->right;
                queueSize++;
            }
        }

        for (i = 0; i < queueSize; i++) {
            queue[i] = queue[i + 1];
        }
        queueSize--;
    }

    free(queue);
}

// Function to build a binary tree
TreeNode* buildTree(int data[], int size) {
    TreeNode* root = NULL;

    for (int i = 0; i < size; i++) {
        if (data[i] == -1)
            continue;
        TreeNode* newNode = createNode(data[i]);

        // Add left child
        if (i * 2 + 1 < size) {
            newNode->left = buildTree(data, i * 2 + 1);
        }

        // Add right child
        if (i * 2 + 2 < size) {
            newNode->right = buildTree(data, i * 2 + 2);
        }
        root = newNode;
    }
    return root;
}

int main() {
    int data[] = {1, 2, -1, 4, 5, -1, -1, 3};
    int size = sizeof(data) / sizeof(data[0]);

    TreeNode* root = buildTree(data, size);

    printf("DFS Traversal: ");
    dfsTraversal(root);
    printf("\n");

    printf("BFS Traversal: ");
    bfsTraversal(root);
    printf("\n");

    return 0;
}