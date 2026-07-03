#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of terms in the Fibonacci sequence: ");
    scanf("%d", &n);

    printf("Fibonacci sequence up to %d:\n", n);
    int t1 = 0, t2 = 1;
    for (int i = 1; i <= n; ++i) {
        if (i == 1) {
            printf("%d ", t1);
        } else if (i == 2) {
            printf("%d ", t2);
        } else {
            int next = t1 + t2;
            printf("%d ", next);
            t1 = t2;
            t2 = next;
        }
    }
    printf("\n");
    return 0;
}