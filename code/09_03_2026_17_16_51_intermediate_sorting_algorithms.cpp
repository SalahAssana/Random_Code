#include <iostream>
#include <chrono>
#include <random>
#include <vector>

// Function to generate random array
std::vector<int> generateRandomArray(int n) {
    std::vector<int> arr(n);
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 100);

    for (int i = 0; i < n; ++i) {
        arr[i] = distribution(generator);
    }

    return arr;
}

// Function to print array
void printArray(const std::vector<int>& arr) {
    for (const auto& num : arr) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}

// Bubble sort function
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// Quicksort function
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Main function
int main() {
    int n = 10000; // Size of the array
    std::vector<int> arr = generateRandomArray(n);

    // Measure time for bubble sort
    auto startBubble = std::chrono::high_resolution_clock::now();
    bubbleSort(arr);
    auto endBubble = std::chrono::high_resolution_clock::now();

    // Measure time for quicksort
    arr = generateRandomArray(n);
    auto startQuicksort = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, n - 1);
    auto endQuicksort = std::chrono::high_resolution_clock::now();

    // Print the array after sorting
    printArray(arr);

    // Calculate and print execution time for bubble sort
    auto bubbleTime = std::chrono::duration_cast<std::chrono::microseconds>(endBubble - startBubble);
    std::cout << "Bubble sort time: " << bubbleTime.count() << " microseconds\n";

    // Calculate and print execution time for quicksort
    auto quicksortTime = std::chrono::duration_cast<std::chrono::microseconds>(endQuicksort - startQuicksort);
    std::cout << "Quicksort time: " << quicksortTime.count() << " microseconds\n";

    return 0;
}