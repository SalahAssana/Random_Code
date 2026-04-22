#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HEIGHT 32
#define ALPHABET_SIZE 256

typedef struct {
    int frequency;
    char character;
} symbol_t;

// Node of Huffman tree
typedef struct node {
    struct node *left, *right;
    int weight;
} node_t;

node_t* create_node(int weight) {
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node->weight = weight;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to build a Huffman tree
node_t* build_tree(symbol_t symbols[], int n) {
    // Priority queue for nodes, ordered by frequency (i.e., priority)
    int i, j, minp;
    node_t *root = NULL, *temp;
    symbol_t *leftbr, *rightbr;

    for (i = 0; i < n; i++) {
        leftbr = &symbols[i];
        rightbr = &symbols[(n - i) + 1];

        // Create leaf nodes and add to priority queue
        temp = create_node(leftbr->frequency);
        temp->character = leftbr->character;
        temp->left = NULL;
        temp->right = NULL;

        temp = create_node(rightbr->frequency);
        temp->character = rightbr->character;
        temp->left = NULL;
        temp->right = NULL;

        if (root == NULL) {
            root = temp;
        } else {
            node_t* curr = root;
            while (1) {
                minp = 0;
                // Find the node with minimum weight
                for (j = 0; j < MAX_TREE_HEIGHT && curr != NULL; j++) {
                    if (curr->weight < minp) {
                        minp = curr->weight;
                    }
                    if (curr->left == NULL || curr->right == NULL) {
                        temp = curr->left;
                        curr->left = curr->right;
                        curr->right = temp;
                        break;
                    }
                    if (j == 0 && curr->left != NULL) {
                        temp = curr->left;
                        curr->left = curr->right;
                        curr->right = temp;
                        break;
                    }
                }

                if (temp == NULL) {
                    break;
                }

                // Add the new node to the tree
                if (minp > 0 && temp != NULL) {
                    node_t* new_node = create_node(minp);
                    new_node->left = curr;
                    new_node->right = temp;
                    root = new_node;
                    minp = 0;
                }
            }
        }
    }

    return root;
}

// Function to calculate the Huffman code for each character
void build_codes(node_t* root, int codes[], char characters[]) {
    if (root == NULL) {
        return;
    } else {
        if (root->character != '\0') {
            codes[root->character] = root->weight;
        }

        if (root->left != NULL && root->right != NULL) {
            build_codes(root->left, codes + 256, characters);
            build_codes(root->right, codes + 256, characters);
        }
    }
}

int main() {
    int n = 26; // number of unique characters
    symbol_t symbols[n];
    for (int i = 0; i < n; i++) {
        symbols[i].frequency = rand();
        symbols[i].character = 'a' + i;
    }

    node_t* root = build_tree(symbols, n);

    int codes[ALPHABET_SIZE];
    char characters[ALPHABET_SIZE];

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        codes[i] = -1;
        characters[i] = '\0';
    }

    build_codes(root, codes, characters);

    // Print the Huffman code for each character
    for (int i = 0; i < n; i++) {
        printf("Character: %c, Code: ", symbols[i].character);
        int j = 256;
        while (j > 0) {
            if ((j >> 1) >= codes[symbols[i].character]) {
                puts("0");
                j >>= 1;
            } else {
                puts("1");
                j -= j / 2;
            }
        }
    }

    return 0;
}