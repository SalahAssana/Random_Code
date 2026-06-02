#include <stdio.h>
#include <stdlib.h>

// Function to swap two elements in an array
void swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Function to partition the array around a pivot element
int partition(int* arr, int low, int high) {
    int pivot = arr[high]; // Choose the last element as pivot
    int i = (low - 1);      // Index of the smaller element

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++; // Increment index of the smaller element
            swap(arr, i, j);
        }
    }

    swap(arr, i + 1, high); // Swap pivot into its final position

    return (i + 1);
}

// Recursive function to implement quicksort
void quicksort(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1); // Recursively sort the left subarray
        quicksort(arr, pi + 1, high); // Recursively sort the right subarray
    }
}

// Function to implement quicksort and print the sorted array
void sortAndPrint(int* arr, int n) {
    quicksort(arr, 0, n - 1);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Driver program to test the above functions
int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));

    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    sortAndPrint(arr, n);

    free(arr);

    return 0;
}