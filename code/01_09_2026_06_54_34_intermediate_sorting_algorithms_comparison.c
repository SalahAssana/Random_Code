#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate random array
void generateArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
}

// Bubble sort algorithm
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

// Quick sort algorithm
void quickSort(int* arr, int low, int high) {
    if (low < high) {
        int pivotIndex = low;
        for (int i = low; i <= high; i++) {
            if (arr[i] < arr[high]) {
                int temp = arr[pivotIndex];
                arr[pivotIndex] = arr[i];
                arr[i] = temp;
                pivotIndex++;
            }
        }
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex, high);
    }
}

// Function to measure time taken for sorting
void measureTime(int* arr, int n) {
    clock_t start, end;
    double diff;

    // Bubble sort
    start = clock();
    bubbleSort(arr, n);
    end = clock();
    diff = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Bubble sort time: %f seconds\n", diff);

    // Quick sort
    start = clock();
    quickSort(arr, 0, n - 1);
    end = clock();
    diff = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Quick sort time: %f seconds\n", diff);
}

int main() {
    int n = 10000; // Array size
    srand(time(NULL)); // Seed random number generator

    int* arr = (int*)malloc(n * sizeof(int));
    generateArray(arr, n);

    measureTime(arr, n);

    free(arr); // Free dynamically allocated memory
    return 0;
}