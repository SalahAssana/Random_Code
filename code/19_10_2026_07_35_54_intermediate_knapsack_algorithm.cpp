#include <iostream>
#include <vector>

struct Item {
    int weight;
    int value;
};

// Function to calculate maximum value that can be put in knapsack
int knapSack(int W, const std::vector<Item>& items, int n) {
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (items[i - 1].weight <= w) {
                int temp = std::max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight],
                                        dp[i - 1][w]);
                dp[i][w] = temp;
            } else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][W];
}

int main() {
    int W = 50; // weight limit
    int n = 4; // number of items

    std::vector<Item> items = {{10, 60}, {20, 100}, {30, 120}, {40, 200}};

    int max_value = knapSack(W, items, n);

    std::cout << "Maximum value that can be put in a knapsack of weight " << W << " is " << max_value << std::endl;

    return 0;
}