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

// Bubble Sort algorithm
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

// Quick Sort algorithm
void quickSort(int* arr, int low, int high) {
    if (low >= high)
        return;
    int pivot = partition(arr, low, high);
    quickSort(arr, low, pivot - 1);
    quickSort(arr, pivot + 1, high);
}

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Function to measure time taken by the sorting algorithm
double measureTime(int* arr, int n, void (*sort)(int*, int)) {
    clock_t start = clock();
    for (int i = 0; i < 10; i++) { // Run the sort function 10 times
        sort(arr, n);
    }
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Function to print the array
void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL)); // Seed random number generator

    int n = 10000;
    int* arr = generateArray(n);

    double bubbleTime = measureTime(arr, n, &bubbleSort);
    double quickTime = measureTime(arr, n, &quickSort);

    printf("Original array: ");
    printArray(arr, n);

    printf("Bubble sort time: %f seconds\n", bubbleTime);
    printf("Quick sort time: %f seconds\n", quickTime);

    return 0;
}