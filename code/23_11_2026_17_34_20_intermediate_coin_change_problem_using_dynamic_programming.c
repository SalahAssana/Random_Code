#include <stdio.h>

int minCoins(int amount, int* coinDenoms, int numCoinDenoms) {
    int dp[amount + 1];
    for (int i = 0; i <= amount; i++) {
        dp[i] = i;
    }

    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < numCoinDenoms; j++) {
            if (coinDenoms[j] <= i) {
                int numCoins = 1 + dp[i - coinDenoms[j]];
                if (numCoins < dp[i]) {
                    dp[i] = numCoins;
                }
            }
        }
    }

    return dp[amount];
}

int main() {
    int amount, numCoinDenoms;
    printf("Enter the total amount: ");
    scanf("%d", &amount);
    printf("Enter the number of coin denominations: ");
    scanf("%d", &numCoinDenoms);

    int* coinDenoms = (int*)malloc(numCoinDenoms * sizeof(int));
    for (int i = 0; i < numCoinDenoms; i++) {
        printf("Enter coin denomination %d: ", i + 1);
        scanf("%d", &coinDenoms[i]);
    }

    int minCoinsNeeded = minCoins(amount, coinDenoms, numCoinDenoms);

    printf("Minimum number of coins needed to make change: %d\n", minCoinsNeeded);

    free(coinDenoms);
    return 0;
}