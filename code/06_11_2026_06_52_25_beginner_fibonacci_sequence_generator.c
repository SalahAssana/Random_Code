#include <stdio.h>
#include <stdlib.h>

int main() {
    int numTerms; // Number of terms in Fibonacci sequence
    printf("Enter number of terms: ");
    scanf("%d", &numTerms);

    int t1 = 0; // First term
    int t2 = 1; // Second term

    printf("Fibonacci sequence up to %d terms:\n", numTerms);
    for (int i = 1; i <= numTerms; ++i) {
        if (i == 1)
            printf("%d ", t1); // Print first term
        else if (i == 2)
            printf("%d ", t2); // Print second term
        else {
            int nextTerm = t1 + t2;
            printf("%d ", nextTerm);
            t1 = t2;
            t2 = nextTerm; // Update terms for next iteration
        }
    }
    printf("\n");

    return 0;
}