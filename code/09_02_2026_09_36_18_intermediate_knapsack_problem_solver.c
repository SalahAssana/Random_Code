#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
typedef struct {
    int weight;
    int value;
} Item;

// Function to solve the 0/1 knapsack problem using dynamic programming
int knapsack(Item items[], int n, int capacity) {
    // Create a table to store the maximum value that can be put in each sub-capacity
    int dp[capacity + 1];
    for (int i = 0; i <= capacity; i++) {
        dp[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = capacity; j >= items[i].weight; j--) {
            // If the current item's value is greater than the maximum value at the previous sub-capacity
            if (items[i].value + dp[j - items[i].weight] > dp[j]) {
                // Update the maximum value
                dp[j] = items[i].value + dp[j - items[i].weight];
            }
        }
    }

    return dp[capacity];
}

int main() {
    // Define the items and their weights and values
    Item items[] = {{2, 3}, {4, 5}, {6, 7}, {8, 9}};
    int n = sizeof(items) / sizeof(items[0]);
    int capacity = 10;

    printf("Maximum value that can be put in the knapsack: %d\n", knapsack(items, n, capacity));

    return 0;
}