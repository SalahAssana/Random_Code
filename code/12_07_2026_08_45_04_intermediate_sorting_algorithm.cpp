#include <iostream>
#include <chrono>
#include <vector>
#include <random>

// Function to swap two elements in an array
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Bubble sort algorithm implementation
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Function to generate random data for testing
std::vector<int> generateRandomData(int size, int maxVal) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, maxVal);

    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// Function to measure and print the time taken by the sorting algorithm
void measureTime(int* arr, int n) {
    auto start = std::chrono::high_resolution_clock::now();
    bubbleSort(arr, n);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Time taken by bubble sort: " << duration.count() << " microseconds" << std::endl;
}

int main() {
    int n = 10000; // Array size
    int maxVal = 1000; // Maximum value for random data generation

    std::vector<int> arr = generateRandomData(n, maxVal);

    // Print original array
    std::cout << "Original array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    bubbleSort(&arr[0], n);

    // Print sorted array
    std::cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    measureTime(&arr[0], n);

    return 0;
}