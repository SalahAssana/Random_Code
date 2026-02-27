#include <stdio.h>

int main() {
    int n; // number of terms to generate
    printf("Enter the number of terms: ");
    scanf("%d", &n);

    int t1 = 0, t2 = 1;
    printf("%d %d ", t1, t2); // print first two terms

    for(int i = 3; i <= n; ++i) {
        int nextTerm = t1 + t2;
        printf("%d ", nextTerm);
        t1 = t2;
        t2 = nextTerm;
    }
    printf("\n");

    return 0;
}