#include <stdio.h>
#include <stdlib.h>

// Function to perform binary search on an array
int binarySearch(int arr[], int target, int low, int high) {
    if (high >= low) {
        // Calculate middle index of the array
        int mid = low + (high - low) / 2;

        // If the target element is present at the midpoint
        if (arr[mid] == target)
            return mid;
        
        // If the target element is smaller than the middle element
        else if (arr[mid] > target)
            return binarySearch(arr, target, low, mid - 1);

        // Target element is larger than the middle element
        else
            return binarySearch(arr, target, mid + 1, high);
    }

    // If we reach here then target was not present in array
    return -1;
}

int main() {
    int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 10;

    int result = binarySearch(arr, target, 0, n-1);

    if (result != -1)
        printf("Element found at index %d.\n", result);
    else
        printf("Element not present in array.\n");

    return 0;
}