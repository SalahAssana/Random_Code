#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Define structure for sorting algorithm information
typedef struct {
    char *name;
    void (*sort)(int*, int);
} SortingAlgorithm;

// Bubble Sort function
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

// Selection Sort function
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

// Function to calculate execution time
double calculateExecutionTime(void (*func)(int*, int), int* arr, int n) {
    clock_t start = clock();
    func(arr, n);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Main function
int main() {
    // Define arrays for sorting algorithms and their respective sizes
    SortingAlgorithm algorithms[] = {
        {"Bubble Sort", bubbleSort},
        {"Selection Sort", selectionSort}
    };
    int sizes[] = {100, 500, 1000};

    // Initialize random number generator
    srand(time(NULL));

    // Create array to store execution times for each algorithm and size
    double* executionTimes = malloc(sizeof(double) * sizeof(algorithms) * sizeof(sizes));
    int i, j;
    for (i = 0; i < sizeof(algorithms) / sizeof(SortingAlgorithm); i++) {
        for (j = 0; j < sizeof(sizes); j++) {
            // Generate random array of specified size
            int* arr = malloc(sizeof(int) * sizes[j]);
            for (int k = 0; k < sizes[j]; k++) {
                arr[k] = rand() % 100;
            }
            // Calculate execution time for current algorithm and size
            double time = calculateExecutionTime(algorithms[i].sort, arr, sizes[j]);
            printf("Algorithm: %s, Size: %d, Execution Time: %.2f seconds\n", algorithms[i].name, sizes[j], time);
            free(arr);
        }
    }

    // Plot execution times using a plotting library (e.g., gnuplot)

    return 0;
}