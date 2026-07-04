#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to calculate the minimum number of scalar multiplications
int minScalarMultiplications(const vector<int>& p, const vector<int>& q) {
    int n = p.size();
    vector<vector<int>> dp(n, vector<int>(n));

    for (int i = 0; i < n; ++i)
        dp[i][i] = 0;

    for (int L = 2; L <= n; ++L) {
        for (int i = 0; i < n - L + 1; ++i) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; ++k) {
                int qkj = p[k] * q[k];
                int cost = dp[i][k] + dp[k + 1][j] + qkj;
                if (cost < dp[i][j])
                    dp[i][j] = cost;
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    // Example input
    vector<int> p = {30, 35, 15, 5};
    vector<int> q = {5, 10, 10, 5};

    cout << "Minimum scalar multiplications: " << minScalarMultiplications(p, q) << endl;

    return 0;
}