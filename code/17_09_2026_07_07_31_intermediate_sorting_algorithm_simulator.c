#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure to represent an array of integers
typedef struct {
    int* data;
    int size;
} Array;

// Function to generate a random array of integers
Array* generateRandomArray(int n) {
    Array* arr = (Array*)malloc(sizeof(Array));
    arr->data = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr->data[i] = rand() % 100;
    }
    arr->size = n;
    return arr;
}

// Function to swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble Sort algorithm
void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Selection Sort algorithm
void selectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(&arr[i], &arr[minIndex]);
    }
}

// Function to print an array
void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL)); // Seed random number generator

    Array* arr1 = generateRandomArray(10);
    Array* arr2 = generateRandomArray(10);

    printf("Original array: ");
    printArray(arr1->data, arr1->size);
    bubbleSort(arr1->data, arr1->size);
    printf("Bubble sort result: ");
    printArray(arr1->data, arr1->size);

    printf("\n");
    printf("Original array: ");
    printArray(arr2->data, arr2->size);
    selectionSort(arr2->data, arr2->size);
    printf("Selection sort result: ");
    printArray(arr2->data, arr2->size);

    free(arr1->data);
    free(arr2->data);
    free(arr1);
    free(arr2);

    return 0;
}