#include <stdio.h>
#include <stdlib.h>

// Structure to represent a graph node
typedef struct {
    int id;
    int color; // -1 if not colored yet
} Node;

// Function to check if two nodes are adjacent (i.e., connected by an edge)
int isAdjacent(Node* nodes, int i, int j) {
    for(int k = 0; k < nodes[i].color; k++) {
        if(nodes[j].id == nodes[i].color[k]) return 1;
    }
    return 0;
}

// Function to check if a color can be assigned to a node
int isValidColor(Node* nodes, int nodeIndex, int color) {
    for(int i = 0; i < nodes[nodeIndex].color; i++) {
        if(isAdjacent(nodes, nodeIndex, nodes[i].id) && nodes[i].color == color) return 0;
    }
    return 1;
}

// Function to assign a color to a node
void assignColor(Node* nodes, int nodeIndex, int color) {
    nodes[nodeIndex].color = color;
}

// Recursive function to solve the graph coloring problem using backtracking
int solveGraphColoring(Node* nodes, int nodeIndex, int maxColors) {
    if(nodeIndex >= (sizeof(nodes)/sizeof(nodes[0]))) return 1; // All nodes colored

    for(int color = 0; color < maxColors; color++) {
        if(isValidColor(nodes, nodeIndex, color)) {
            assignColor(nodes, nodeIndex, color);
            if(solveGraphColoring(nodes, nodeIndex + 1, maxColors)) return 1;
            // Backtrack: reset the color and try another one
            assignColor(nodes, nodeIndex, -1);
        }
    }

    return 0; // No valid coloring found
}

// Main function to test the graph coloring algorithm
int main() {
    Node nodes[] = {{0}, {1}, {2}, {3}, {4}};
    int maxColors = 3;
    if(solveGraphColoring(nodes, 0, maxColors)) {
        printf("Valid coloring found:\n");
        for(int i = 0; i < sizeof(nodes)/sizeof(nodes[0]); i++) {
            printf("%d -> %d\n", nodes[i].id, nodes[i].color);
        }
    } else {
        printf("No valid coloring found.\n");
    }
    return 0;
}