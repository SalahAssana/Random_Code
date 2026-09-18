#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

// Sorting algorithms
void bubbleSort(std::vector<int>& arr) {
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < arr.size() - 1; ++i) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // choosing the last element as pivot
    int i = (low - 1);

    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Function to generate random array
std::vector<int> generateRandomArray(int n, int maxVal) {
    std::vector<int> arr;
    for (int i = 0; i < n; ++i) {
        arr.push_back(rand() % maxVal);
    }
    return arr;
}

// Function to measure the time taken by a sorting algorithm
void measureTime(std::vector<int>& arr, const char* algoName) {
    auto start = std::chrono::high_resolution_clock::now();
    if (strcmp(algoName, "Bubble Sort") == 0) {
        bubbleSort(arr);
    } else if (strcmp(algoName, "Quick Sort") == 0) {
        quickSort(arr, 0, arr.size() - 1);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << algoName << ": Time taken - "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds" << std::endl;
}

int main() {
    srand(time(0));
    const int n = 10000;
    const int maxVal = 100;

    // Generate a random array
    std::vector<int> arr = generateRandomArray(n, maxVal);

    // Measure the time taken by each sorting algorithm
    measureTime(arr, "Bubble Sort");
    measureTime(arr, "Quick Sort");

    return 0;
}