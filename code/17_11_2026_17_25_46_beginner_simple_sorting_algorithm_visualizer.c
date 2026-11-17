#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate random array of size n
int* generateArray(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
    return arr;
}

// Function to print array
void printArray(int* arr, int n) {
    printf("[");
    for (int i = 0; i < n - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[n - 1]);
}

// Function to perform bubble sort
void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to perform selection sort
void selectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

// Main function
int main() {
    srand(time(NULL)); // Seed random number generator

    int n = 10; // Size of array
    int* arr = generateArray(n);

    printf("Original array:\n");
    printArray(arr, n);

    bubbleSort(arr, n);
    printf("After Bubble Sort:\n");
    printArray(arr, n);

    selectionSort(arr, n);
    printf("After Selection Sort:\n");
    printArray(arr, n);

    free(arr); // Free dynamically allocated memory

    return 0;
}