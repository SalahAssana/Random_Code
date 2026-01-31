#include <stdio.h>

// Function to calculate the Fibonacci sequence up to a given number of terms
void fibonacci(int n) {
    int t1 = 0, t2 = 1;
    printf("%d %d ", t1, t2);

    for (int i = 3; i <= n; ++i) {
        int nextTerm = t1 + t2;
        printf("%d ", nextTerm);
        t1 = t2;
        t2 = nextTerm;
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of terms: ");
    scanf("%d", &n);
    fibonacci(n);
    return 0;
}