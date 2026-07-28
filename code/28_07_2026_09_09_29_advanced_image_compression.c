#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WIDTH 256
#define MAX_HEIGHT 256
#define MAX_PIXELS (MAX_WIDTH * MAX_HEIGHT)

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Pixel;

// Function to get the frequency of each pixel color value
int* getFrequency(Pixel* pixels, int* width, int* height) {
    int* freq = (int*)malloc((MAX_WIDTH * MAX_HEIGHT + 1)*sizeof(int));
    for (int i = 0; i < *width * *height; i++) {
        int val = ((pixels[i].red >> 5) | ((pixels[i].green >> 5) << 3) | ((pixels[i].blue >> 5) << 6));
        freq[val]++;
    }
    return freq;
}

// Function to build the Huffman tree
typedef struct Node {
    char symbol;
    int frequency;
    struct Node* left;
    struct Node* right;
} Node;

Node* buildTree(int* freq, int size) {
    Node* nodes = (Node*)malloc(size * sizeof(Node));
    for (int i = 0; i < size; i++) {
        nodes[i].symbol = '0' + i;
        nodes[i].frequency = freq[i];
        nodes[i].left = NULL;
        nodes[i].right = NULL;
    }
    Node* root = buildTreeHelper(nodes, 0, size);
    free(nodes);
    return root;
}

Node* buildTreeHelper(Node* nodes, int start, int end) {
    if (end <= start + 1) {
        return nodes[start];
    }
    Node* node = (Node*)malloc(sizeof(Node));
    node->symbol = 'x';
    node->frequency = nodes[start].frequency + nodes[end - 1].frequency;
    node->left = buildTreeHelper(nodes, start, (end + start) / 2);
    node->right = buildTreeHelper(nodes, (end + start) / 2, end);
    return node;
}

// Function to encode the image using Huffman coding
void encode(Pixel* pixels, int* width, int* height, Node* root, char** compressed) {
    *compressed = (char*)malloc((MAX_WIDTH * MAX_HEIGHT)*sizeof(char));
    for (int i = 0; i < *width * *height; i++) {
        Node* current = root;
        for (int j = 0; j < 8; j++) {
            if (((pixels[i].red >> 5) | ((pixels[i].green >> 5) << 3) | ((pixels[i].blue >> 5) << 6)) & 1)
                current = current->right;
            else
                current = current->left;
        }
        (*compressed)[i] = current->symbol;
    }
}

int main() {
    Pixel pixels[MAX_PIXELS];
    int width, height;
    // Initialize the image data here

    int* freq = getFrequency(pixels, &width, &height);
    Node* root = buildTree(freq, MAX_WIDTH * MAX_HEIGHT + 1);
    char* compressed = NULL;
    encode(pixels, &width, &height, root, &compressed);

    // Print the compressed data here

    return 0;
}