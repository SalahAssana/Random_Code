#include <iostream>
#include <vector>

// Function to generate Fibonacci series up to nth number
std::vector<int> fibonacci(int n) {
    std::vector<int> fibSeries;
    int a = 0, b = 1;

    // Generate Fibonacci series up to nth number
    for (int i = 0; i < n; i++) {
        fibSeries.push_back(a);
        int temp = a;
        a = b;
        b = temp + b;
    }

    return fibSeries;
}

// Function to display the Fibonacci series in descending order
void displayFibonacci(const std::vector<int>& fibSeries) {
    // Reverse the vector to display in descending order
    for (int i = fibSeries.size() - 1; i >= 0; i--) {
        std::cout << fibSeries[i] << " ";
    }
}

// Main function to test the code
int main() {
    int n;
    std::cout << "Enter the number of Fibonacci numbers to generate: ";
    std::cin >> n;

    // Generate and display the Fibonacci series in descending order
    std::vector<int> fibSeries = fibonacci(n);
    std::cout << "\nFibonacci Series up to " << n << " numbers: \n";
    displayFibonacci(fibSeries);

    return 0;
}