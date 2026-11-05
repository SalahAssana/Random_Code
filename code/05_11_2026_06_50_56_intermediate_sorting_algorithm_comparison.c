#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate random array of size n
int* generateArray(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
    return arr;
}

// Function to calculate time taken by a function
double calculateTime(int* arr, int n) {
    clock_t start = clock();
    // Call the sorting algorithm here (bubble sort for example)
    bubbleSort(arr, n);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    return time_taken;
}

// Bubble sort function
void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Insertion sort function
void insertionSort(int* arr, int n) {
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

int main() {
    const int n = 10000; // Size of the array
    int* arr = generateArray(n);
    
    double bubble_sort_time = calculateTime(arr, n);
    printf("Bubble sort time: %f seconds\n", bubble_sort_time);
    
    insertionSort(arr, n); // Perform insertion sort on the array
    
    double insertion_sort_time = calculateTime(arr, n);
    printf("Insertion sort time: %f seconds\n", insertion_sort_time);
    
    free(arr);
    return 0;
}