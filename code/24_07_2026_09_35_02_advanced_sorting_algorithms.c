#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

// Function prototypes
void bubbleSort(int* arr, int n);
void quicksort(int* arr, int low, int high);
int partition(int* arr, int low, int high);
void printArray(int* arr, int n);

// Structure to represent a benchmarking result
typedef struct {
    char* algorithm;
    double time;
} BenchmarkResult;

// Function to compare and sort arrays using different algorithms
BenchmarkResult* sortArrays(int** dataSets, int numDataSets, int size) {
    BenchmarkResult* results = (BenchmarkResult*)malloc(numDataSets * sizeof(BenchmarkResult));
    for (int i = 0; i < numDataSets; i++) {
        int* arr = dataSets[i];
        clock_t start = clock();
        bubbleSort(arr, size);
        double bubbleTime = (double)(clock() - start) / CLOCKS_PER_SEC;

        start = clock();
        quicksort(arr, 0, size - 1);
        double quickTime = (double)(clock() - start) / CLOCKS_PER_SEC;

        results[i].algorithm = i % 2 == 0 ? "Bubble Sort" : "Quicksort";
        results[i].time = i % 2 == 0 ? bubbleTime : quickTime;
    }
    return results;
}

// Main function
int main() {
    srand(time(NULL));

    // Create some sample data sets
    int** dataSets = (int**)malloc(3 * sizeof(int*));
    for (int i = 0; i < 3; i++) {
        int size = rand() % 10 + 1;
        int* arr = (int*)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            arr[j] = rand() % 100;
        }
        dataSets[i] = arr;
    }

    // Benchmark the sorting algorithms
    BenchmarkResult* results = sortArrays(dataSets, 3, 10);

    // Print the results
    for (int i = 0; i < 3; i++) {
        printf("%s took %.2f seconds\n", results[i].algorithm, results[i].time);
    }

    // Free memory
    for (int i = 0; i < 3; i++) {
        free(dataSets[i]);
    }
    free(dataSets);
    free(results);

    return 0;
}

// Bubble sort function
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

// Quicksort function
void quicksort(int* arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }
}

// Partition function for quicksort
int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// Function to print an array
void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}