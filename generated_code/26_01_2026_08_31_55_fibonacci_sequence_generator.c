#include <stdio.h>
#include <stdlib.h>

// Function to calculate the nth Fibonacci number
long long fibonacci(int n) {
    if (n <= 1)
        return n;
    long long a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        long long temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

// Function to generate and print the first N Fibonacci numbers
void printFibonacci(int N) {
    for (int i = 0; i < N; i++) {
        printf("%lld ", fibonacci(i));
    }
    printf("\n");
}

int main() {
    int N;
    printf("Enter the number of Fibonacci numbers to generate: ");
    scanf("%d", &N);
    printFibonacci(N);
    return 0;
}