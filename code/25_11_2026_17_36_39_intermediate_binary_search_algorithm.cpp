#include <iostream>
#include <algorithm>

// Function to perform binary search on an array of integers
int binarySearch(int arr[], int n, int target) {
    // Initialize low and high indices for binary search
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        // Calculate the middle index
        int mid = (low + high) / 2;

        // Check if the target element is found at the middle index
        if (arr[mid] == target) {
            return mid; // Return the index of the target element
        }
        else if (arr[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    // If the target element is not found, return -1
    return -1;
}

int main() {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target;

    // Ask the user to input a target element
    std::cout << "Enter a number to search: ";
    std::cin >> target;

    // Call the binarySearch function and store the result
    int result = binarySearch(arr, n, target);

    if (result != -1) {
        std::cout << "Element found at index " << result << std::endl;
    }
    else {
        std::cout << "Element not found in the array." << std::endl;
    }

    return 0;
}