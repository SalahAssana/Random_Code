#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the sorting algorithms
void bubbleSort(int arr[], int n);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);
void mergeSort(int arr[], int n);

// Function to generate random array of size 'n' with values from 0 to 'max'
int* generateRandomArray(int n, int max) {
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (max + 1);
    }
    return arr;
}

// Function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL)); // Seed random number generator

    const int n = 100;
    const int max = 100;

    // Generate random array
    int* arr = generateRandomArray(n, max);

    // Print original array
    printf("Original Array: ");
    printArray(arr, n);

    // Sort the array using each algorithm and measure time taken
    clock_t start, end;
    double bubbleSortTime = 0.0, selectionSortTime = 0.0, insertionSortTime = 0.0, mergeSortTime = 0.0;

    start = clock();
    bubbleSort(arr, n);
    end = clock();
    bubbleSortTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Bubble Sort Time: %f seconds\n", bubbleSortTime);

    start = clock();
    selectionSort(arr, n);
    end = clock();
    selectionSortTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Selection Sort Time: %f seconds\n", selectionSortTime);

    start = clock();
    insertionSort(arr, n);
    end = clock();
    insertionSortTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Insertion Sort Time: %f seconds\n", insertionSortTime);

    start = clock();
    mergeSort(arr, n);
    end = clock();
    mergeSortTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Merge Sort Time: %f seconds\n", mergeSortTime);

    // Print sorted array
    printf("Sorted Array: ");
    printArray(arr, n);

    return 0;
}

void bubbleSort(int arr[], int n) {
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

void selectionSort(int arr[], int n) {
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

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void mergeSort(int arr[], int n) {
    if (n <= 1) return;

    int mid = n / 2;
    int left[n / 2], right[n - mid];

    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    for (int i = mid; i < n; i++) {
        right[i - mid] = arr[i];
    }

    mergeSort(left, mid);
    mergeSort(right, n - mid);

    int k = 0;
    while (k < mid && k < n - mid) {
        if (left[k] <= right[k]) {
            arr[k] = left[k];
            k++;
        } else {
            arr[k] = right[k - mid];
            k++;
        }
    }

    while (k < mid) {
        arr[k] = left[k];
        k++;
    }

    while (k < n - mid) {
        arr[k] = right[k - mid];
        k++;
    }
}