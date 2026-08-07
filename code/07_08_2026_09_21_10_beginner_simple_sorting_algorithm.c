#include <stdio.h>

// Function to swap two elements in an array
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Function to partition the array and return the pivot index
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choose the last element as pivot
    int i = (low - 1); // Index of the smaller element

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++; // Increment index of the smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]); // Swap the pivot with the element at index i
    return (i + 1);
}

// Function to implement quicksort algorithm
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Partition the array and get the pivot index

        // Recursively call quicksort on the left subarray
        quickSort(arr, low, pi - 1);

        // Recursively call quicksort on the right subarray
        quickSort(arr, pi + 1, high);
    }
}

// Function to print the array elements
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {5, 2, 8, 6, 1, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Call the quicksort function
    quickSort(arr, 0, n - 1);

    // Print the sorted array
    printf("Sorted array: ");
    printArray(arr, n);
    return 0;
}