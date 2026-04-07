#include <stdio.h>
#include <stdlib.h>

#define MAX_WEIGHT 1000
#define MAX_ITEMS 10

// Function to calculate maximum value that can be put in knapsack
int max_value(int w[], int n, int W) {
    int i, val = 0;
    for (i = 0; i < n; i++) {
        if (w[i] <= W) {
            val = val + w[i];
            W = W - w[i];
        } else {
            int k = W / (w[i] + 1);
            val = val + k * w[i];
            W = W - k * w[i];
            break;
        }
    }
    return val;
}

// Function to get maximum value using dynamic programming
int max_value_dp(int w[], int n, int W) {
    int dp[W + 1], i, j;

    // Initialize all values in DP array as 0
    for (j = 0; j <= W; j++) {
        dp[j] = 0;
    }

    // Fill DP array using bottom-up dynamic programming approach
    for (i = 1; i <= n; i++) {
        for (j = w[i - 1]; j <= W; j++) {
            if (w[i - 1] <= j)
                dp[j] = max(dp[j], dp[j - w[i - 1]] + w[i - 1]);
            else
                dp[j] = dp[j];
        }
    }

    return dp[W];
}

int main() {
    int i, n;
    printf("Enter number of items: ");
    scanf("%d", &n);
    int w[MAX_ITEMS], val[MAX_ITEMS];

    // Input weights and values for each item
    for (i = 0; i < n; i++) {
        printf("Enter weight and value for item %d: ", i + 1);
        scanf("%d %d", &w[i], &val[i]);
    }

    int W;
    printf("Enter maximum weight capacity: ");
    scanf("%d", &W);

    // Calculate maximum value using dynamic programming
    int max_val = max_value_dp(w, n, W);

    // Print the result
    printf("Maximum value that can be put in knapsack is %d\n", max_val);

    return 0;
}