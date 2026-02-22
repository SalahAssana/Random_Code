#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to generate Fibonacci sequence
void fibonacci(int length, int* seq) {
    int a = 0;
    int b = 1;

    for (int i = 0; i < length; i++) {
        seq[i] = a;
        if (i >= 1) {
            seq[i] = seq[i - 1] + seq[i - 2];
        }
        a = b;
        b = seq[i];
    }
}

// Function to generate prime numbers sequence
void primes(int length, int* seq) {
    bool isPrime;

    for (int i = 0; i < length; i++) {
        isPrime = true;
        for (int j = 2; j * j <= i + 1; j++) {
            if ((i + 1) % j == 0) {
                isPrime = false;
                break;
            }
        }
        seq[i] = isPrime ? i + 1 : -1; // Replace -1 with actual value if needed
    }
}

int main() {
    int length, choice;

    printf("Enter the sequence length: ");
    scanf("%d", &length);

    int* seq = (int*)malloc(length * sizeof(int));

    printf("Choose a sequence type:\n");
    printf("1. Fibonacci\n");
    printf("2. Prime numbers\n");
    printf("3. Exit\n");

    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fibonacci(length, seq);
            break;
        case 2:
            primes(length, seq);
            break;
        case 3:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Exiting...\n");
            return 0;
    }

    for (int i = 0; i < length; i++) {
        printf("%d ", seq[i]);
    }
    printf("\n");

    free(seq);

    return 0;
}