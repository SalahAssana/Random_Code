#include <iostream>
#include <vector>

// Function to implement bubble sort algorithm
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break; // If no two elements were swapped in a pass, array is sorted
    }
}

// Function to print the array
void printArray(const std::vector<int>& arr) {
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Create a sample array
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    // Call the bubble sort function
    bubbleSort(arr);

    // Print the sorted array
    printArray(arr);

    return 0;
}