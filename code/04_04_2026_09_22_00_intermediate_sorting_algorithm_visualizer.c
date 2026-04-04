#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000
#define SWAP(a, b) do { int t = a; a = b; b = t; } while (0)

// Structure to represent an array of integers with swap functionality
typedef struct {
    int* data;
    int size;
} Array;

// Function to initialize an empty array
Array init_array(int size) {
    Array arr = {malloc(size * sizeof(int)), size};
    for (int i = 0; i < size; i++) {
        arr.data[i] = rand() % 100;
    }
    return arr;
}

// Bubble Sort function
void bubble_sort(Array* arr) {
    int n = arr->size;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr->data[j] > arr->data[j + 1]) {
                SWAP(arr->data[j], arr->data[j + 1]);
            }
        }
    }
}

// Quick Sort function
void quick_sort(Array* arr, int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quick_sort(arr, low, pivot - 1);
        quick_sort(arr, pivot + 1, high);
    }
}

int partition(Array* arr, int low, int high) {
    int pivot = arr->data[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr->data[j] < pivot) {
            i++;
            SWAP(arr->data[i], arr->data[j]);
        }
    }

    SWAP(arr->data[i + 1], arr->data[high]);
    return (i + 1);
}

// Function to print the array
void print_array(Array* arr) {
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    Array arr = init_array(MAX_SIZE);
    printf("Original array: \n");
    print_array(&arr);

    bubble_sort(&arr);
    printf("Bubble Sort: \n");
    print_array(&arr);

    quick_sort(&arr, 0, arr.size - 1);
    printf("Quick Sort: \n");
    print_array(&arr);

    return 0;
}