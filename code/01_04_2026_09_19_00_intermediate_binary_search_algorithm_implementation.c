#include <stdio.h>
#include <stdlib.h>

// Function to perform binary search on a sorted array
int binarySearch(int* arr, int target, int left, int right) {
    if (left > right) {
        return -1; // Element not found in the array
    }

    int mid = left + (right - left) / 2;

    // Check if target is present at the mid index
    if (arr[mid] == target) {
        return mid;
    }

    // If target is greater, ignore left half
    if (arr[mid] < target) {
        return binarySearch(arr, target, mid + 1, right);
    }

    // If target is smaller, ignore right half
    return binarySearch(arr, target, left, mid - 1);
}

int main() {
    int arr[10] = {2, 3, 4, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Sort the array in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // Find an element using binary search
    int target = 10;
    int result = binarySearch(arr, target, 0, n - 1);

    if (result != -1) {
        printf("Element found at index %d.\n", result);
    } else {
        printf("Element not found in the array.\n");
    }

    return 0;
}