#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define structure for array element
typedef struct {
    int value;
    int color; // 0: white, 1: gray, 2: blue (sorted)
} ArrayElement;

// Function to swap two elements in the array
void swap(ArrayElement* a, int i, int j) {
    ArrayElement temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

// Bubble sort algorithm
void bubbleSort(ArrayElement* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].value > arr[j + 1].value) {
                swap(arr, j, j + 1);
            }
        }
    }
}

// Function to print the array
void printArray(ArrayElement* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d (%s)\n", arr[i].value, arr[i].color == 2 ? "blue" : arr[i].color == 1 ? "gray" : "white");
    }
}

// Main function
int main() {
    // Initialize random seed
    srand(time(NULL));

    // Define the array size and initialize with random values
    int n = 10;
    ArrayElement* arr = (ArrayElement*)malloc(n * sizeof(ArrayElement));
    for (int i = 0; i < n; i++) {
        arr[i].value = rand() % 100;
        arr[i].color = 0; // Initialize with white
    }

    printf("Original array:\n");
    printArray(arr, n);

    // Sort the array using bubble sort
    bubbleSort(arr, n);

    printf("\nSorted array:\n");
    printArray(arr, n);

    free(arr);
    return 0;
}