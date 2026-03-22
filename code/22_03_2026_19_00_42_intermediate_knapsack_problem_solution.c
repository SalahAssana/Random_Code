#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item in the knapsack problem
typedef struct {
    int weight;
    int value;
} Item;

// Function to solve the 0/1 knapsack problem using dynamic programming
int knapsack(int capacity, Item items[], int n) {
    // Create a table to store the maximum value that can be obtained for each subproblem
    int dp[n + 1][capacity + 1];

    // Initialize the table with zeros
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= capacity; j++) {
            dp[i][j] = 0;
        }
    }

    // Fill the table in a bottom-up manner
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (items[i - 1].weight > w) {
                dp[i][w] = dp[i - 1][w];
            } else {
                // Choose the maximum value between including and excluding the current item
                dp[i][w] = (dp[i - 1][w] > items[i - 1].value + dp[i - 1][w - items[i - 1].weight]) ? 
                    dp[i - 1][w] : items[i - 1].value + dp[i - 1][w - items[i - 1].weight];
            }
        }
    }

    // Return the maximum value that can be obtained
    return dp[n][capacity];
}

int main() {
    // Define a sample knapsack problem with 5 items and a capacity of 10 units
    Item items[] = {{2, 3}, {4, 4}, {6, 7}, {8, 8}, {9, 9}};
    int n = sizeof(items) / sizeof(Item);
    int capacity = 10;

    // Solve the knapsack problem using dynamic programming
    int maxValue = knapsack(capacity, items, n);

    printf("The maximum value that can be obtained is: %d\n", maxValue);

    return 0;
}