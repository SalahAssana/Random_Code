#include <stdio.h>
#include <stdlib.h>

// Function to calculate the minimum number of coins required to make change
int minCoins(int *coins, int n, int amount) {
    int dp[amount + 1];
    for (int i = 0; i <= amount; i++) {
        dp[i] = amount + 1;
    }
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n && coins[j] <= i; j++) {
            if (i - coins[j] >= 0) {
                int temp = dp[i - coins[j]] + 1;
                if (temp < dp[i]) {
                    dp[i] = temp;
                }
            }
        }
    }

    return dp[amount];
}

int main() {
    int coins[] = {1, 2, 5};
    int n = sizeof(coins) / sizeof(coins[0]);
    int amount = 11;

    printf("Minimum number of coins required to make change: %d\n", minCoins(coins, n, amount));

    return 0;
}