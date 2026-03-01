#include <stdio.h>
#include <stdlib.h>

// Define the structure for Huffman tree node
typedef struct HuffNode {
    char symbol;
    int frequency;
    struct HuffNode* left;
    struct HuffNode* right;
} HuffNode;

// Define the structure for Huffman coding table
typedef struct HuffTable {
    HuffNode* root;
    int size;
} HuffTable;

// Function to calculate the frequency of each character in the input string
int* calculateFrequency(char* str, int n) {
    int freq[256] = {0};
    for (int i = 0; i < n; i++) {
        freq[(int)str[i]]++;
    }
    return freq;
}

// Function to build Huffman tree using frequency array
HuffTable* buildHuffmanTree(int* frequency, int n) {
    HuffNode** nodes = (HuffNode**)malloc((n + 1) * sizeof(HuffNode*));
    for (int i = 0; i <= n; i++) {
        nodes[i] = (HuffNode*)malloc(sizeof(HuffNode));
        nodes[i]->symbol = 'a' + i;
        nodes[i]->frequency = frequency[i];
        nodes[i]->left = NULL;
        nodes[i]->right = NULL;
    }

    HuffTable* table = (HuffTable*)malloc(sizeof(HuffTable));
    table->root = heapify(nodes, n);
    table->size = n;

    for (int i = 0; i <= n; i++) {
        free(nodes[i]);
    }
    free(nodes);

    return table;
}

// Function to perform heapify on the given array of nodes
HuffNode* heapify(HuffNode** nodes, int n) {
    HuffNode* node;
    for (int i = (n / 2) - 1; i >= 0; i--) {
        node = nodes[i];
        int smallest = leftChild(i);
        if (smallest > -1 && nodes[smallest]->frequency < node->frequency) {
            swapNodes(&nodes[i], &nodes[smallest]);
            smallest = leftChild(smallest);
            if (smallest > -1 && nodes[smallest]->frequency < node->frequency) {
                swapNodes(&nodes[i], &nodes[smallest]);
            }
        }
    }

    return nodes[0];
}

// Function to find the left child of a given node
int leftChild(int i) {
    return 2 * i + 1;
}

// Function to perform swapping between two nodes
void swapNodes(HuffNode** a, HuffNode** b) {
    HuffNode* temp = *a;
    *a = *b;
    *b = temp;
}

// Function to compress the input string using Huffman coding
char* huffmanCompress(char* str, HuffTable* table) {
    char* compressed = (char*)malloc(strlen(str) + 1);
    HuffNode* current = table->root;

    for (int i = 0; i < strlen(str); i++) {
        if (current->left != NULL && current->symbol == 'a' + str[i]) {
            current = current->left;
        } else if (current->right != NULL && current->symbol == 'a' + str[i]) {
            current = current->right;
        }
    }

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] < 'e') {
            strcat(compressed, "0");
        } else {
            strcat(compressed, "1");
        }
    }

    free(table);
    return compressed;
}

// Function to decompress the input string using Huffman coding
char* huffmanDecompress(char* str, HuffTable* table) {
    char* decompressed = (char*)malloc(strlen(str) + 1);
    HuffNode* current = table->root;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (current->left == NULL && current->right == NULL) {
            strcat(decompressed, &current->symbol);
            current = table->root;
        }
    }

    free(table);
    return decompressed;
}

int main() {
    char* str = "this is an example for huffman coding";
    int n = strlen(str);

    // Calculate frequency of each character
    int* frequency = calculateFrequency(str, n);

    // Build Huffman tree using frequency array
    HuffTable* table = buildHuffmanTree(frequency, n);

    // Compress the input string using Huffman coding
    char* compressed = huffmanCompress(str, table);
    printf("Compressed string: %s\n", compressed);

    // Decompress the input string using Huffman coding
    char* decompressed = huffmanDecompress(compressed, table);
    printf("Decompressed string: %s\n", decompressed);

    return 0;
}