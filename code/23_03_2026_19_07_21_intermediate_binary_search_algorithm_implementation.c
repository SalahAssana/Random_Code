#include <stdio.h>
#include <stdlib.h>

// Function to perform binary search
int binarySearch(int arr[], int target, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check if the target is present at the mid index
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; // Target not found in array
}

// Function to generate a random array of integers
int* generateArray(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Random integer between 0 and 99
    }
    return arr;
}

// Function to test the binary search algorithm
void testBinarySearch() {
    int n = 10000; // Array size
    int* arr = generateArray(n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int target = rand() % 100; // Random target integer between 0 and 99
    int result = binarySearch(arr, target, 0, n - 1);
    if (result != -1) {
        printf("Target found at index %d\n", result);
    } else {
        printf("Target not found in array\n");
    }

    free(arr); // Free dynamically allocated memory
}

int main() {
    testBinarySearch();
    return 0;
}