#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate random array of integers
int* generateRandomArray(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
    return arr;
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

// Function to perform quicksort
void quickSort(int* arr, int low, int high) {
    if (low >= high)
        return;
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
    int temp2 = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp2;
    quickSort(arr, low, i);
    quickSort(arr, i + 1, high);
}

// Function to perform selection sort
void selectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

// Function to print the array
void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    int n = 100;
    int* arr = generateRandomArray(n);
    
    // Bubble sort
    clock_t startBubble = clock();
    bubbleSort(arr, n);
    double timeBubble = (double)(clock() - startBubble) / CLOCKS_PER_SEC;
    printf("Bubble sort: ");
    printArray(arr, n);
    printf("Time taken: %f seconds\n", timeBubble);

    // Quicksort
    int lowQuicksort = 0;
    int highQuicksort = n - 1;
    clock_t startQuicksort = clock();
    quickSort(arr, lowQuicksort, highQuicksort);
    double timeQuicksort = (double)(clock() - startQuicksort) / CLOCKS_PER_SEC;
    printf("Quicksort: ");
    printArray(arr, n);
    printf("Time taken: %f seconds\n", timeQuicksort);

    // Selection sort
    clock_t startSelection = clock();
    selectionSort(arr, n);
    double timeSelection = (double)(clock() - startSelection) / CLOCKS_PER_SEC;
    printf("Selection sort: ");
    printArray(arr, n);
    printf("Time taken: %f seconds\n", timeSelection);

    free(arr);
    return 0;
}