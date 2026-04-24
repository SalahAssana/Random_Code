#include <stdio.h>
#include <stdlib.h>

// Function to perform binary search
int binarySearch(int* arr, int target, int low, int high) {
    if (high >= low) {
        // Calculate mid index
        int mid = low + (high - low) / 2;

        // Check if the element is present at the mid index
        if (arr[mid] == target)
            return mid;
        
        // If element is smaller than mid, repeat for left half
        else if (arr[mid] > target)
            return binarySearch(arr, target, low, mid - 1);
        
        // Else, repeat for right half
        else
            return binarySearch(arr, target, mid + 1, high);
    }
    
    // Element not found in array
    return -1;
}

// Function to print the array
void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // Sample array data
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int target;
    printf("Enter the number to search: ");
    scanf("%d", &target);
    
    // Perform binary search
    int result = binarySearch(arr, target, 0, n - 1);
    
    if (result == -1)
        printf("Element not found in array.\n");
    else
        printf("Element found at index %d.\n", result);
    
    return 0;
}