#include <iostream>
using namespace std;

// Function to calculate nth Fibonacci number
long long fibonacci(int n) {
    // Base cases for Fibonacci sequence
    if (n <= 1)
        return n;
    
    // Initialize first two numbers in the sequence
    long long a = 0, b = 1;
    
    // Calculate remaining numbers in the sequence
    for (int i = 2; i < n; i++) {
        long long temp = a;
        a = b;
        b = temp + b;
    }
    
    return b;
}

int main() {
    int numTerms;
    
    cout << "Enter the number of terms in the Fibonacci sequence: ";
    cin >> numTerms;
    
    for (int i = 0; i < numTerms; i++) {
        long long result = fibonacci(i);
        cout << "Fibonacci term " << i + 1 << ": " << result << endl;
    }
    
    return 0;
}