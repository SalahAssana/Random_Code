#include <iostream>
#include <vector>
#include <algorithm>

// Function to perform merge sort on an array of integers
void mergeSort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;

    int mid = arr.size() / 2;
    std::vector<int> left(arr.begin(), arr.begin() + mid);
    std::vector<int> right(arr.begin() + mid, arr.end());

    mergeSort(left);
    mergeSort(right);

    int i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] > right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    // Copy remaining elements from the two halves
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

// Function to print an array of integers
void printArray(const std::vector<int>& arr) {
    for (int i : arr) std::cout << i << " ";
    std::cout << std::endl;
}

// Main function
int main() {
    // Create a sample array
    std::vector<int> arr = {4, 2, 9, 6, 23, 12, 34, 21};

    // Print the original array
    std::cout << "Original array: ";
    printArray(arr);

    // Perform merge sort on the array
    mergeSort(arr);

    // Print the sorted array in descending order
    std::cout << "Sorted array (descending): ";
    printArray(arr);

    return 0;
}