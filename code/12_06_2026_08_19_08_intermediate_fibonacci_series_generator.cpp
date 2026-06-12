#include <iostream>
#include <vector>

// Function to calculate Fibonacci series using recursion
int fibonacciRecursive(int n) {
    if (n <= 1)
        return n;
    else
        return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

// Function to calculate Fibonacci series using iteration
std::vector<int> fibonacciIterative(int n) {
    std::vector<int> fibSeries;
    int a = 0, b = 1;

    for (int i = 0; i < n; i++) {
        if (i <= 1)
            fibSeries.push_back(i);
        else
            fibSeries.push_back(a + b), a = b, b = a + b;
    }

    return fibSeries;
}

int main() {
    int n;

    std::cout << "Enter the number of Fibonacci series terms: ";
    std::cin >> n;

    // Calculate Fibonacci series using recursion
    for (int i = 0; i < n; i++) {
        if (i <= 1)
            std::cout << i << " ";
        else
            std::cout << fibonacciRecursive(i) << " ";
    }
    std::cout << std::endl;

    // Calculate Fibonacci series using iteration
    for (int i = 0; i < n; i++) {
        if (i <= 1)
            std::cout << i << " ";
        else
            std::cout << fibonacciIterative(n)[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}