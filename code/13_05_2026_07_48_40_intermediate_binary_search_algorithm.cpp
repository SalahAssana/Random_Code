#include <iostream>
#include <vector>

// Function to perform binary search on a sorted array
int binarySearch(const std::vector<int>& arr, int target) {
    // Initialize low and high indices for binary search
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        // Calculate the mid index
        int mid = (low + high) / 2;

        if (arr[mid] == target) {
            // Target element found, return its index
            return mid;
        } else if (arr[mid] < target) {
            // Search in the right half of the array
            low = mid + 1;
        } else {
            // Search in the left half of the array
            high = mid - 1;
        }
    }

    // Target element not found, return -1
    return -1;
}

int main() {
    // Example sorted array for testing
    std::vector<int> arr = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};

    int target = 23; // Element to search for

    int result = binarySearch(arr, target);

    if (result != -1) {
        std::cout << "Element found at index " << result << "." << std::endl;
    } else {
        std::cout << "Element not found in the array." << std::endl;
    }

    return 0;
}