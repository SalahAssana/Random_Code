#include <stdio.h>

int fibonacci(int n) {
    int t1 = 0, t2 = 1;
    for (int i = 3; i <= n; i++) {
        int temp = t1 + t2;
        t1 = t2;
        t2 = temp;
    }
    return t2;
}

int main() {
    int numTerms;
    printf("Enter the number of terms in the Fibonacci series: ");
    scanf("%d", &numTerms);

    for (int i = 0; i < numTerms; i++) {
        printf("%d ", fibonacci(i + 1));
    }
    printf("\n");

    return 0;
}