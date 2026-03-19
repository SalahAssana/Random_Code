#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

// Function to generate random array
int* generateRandomArray(int n) {
    int* arr = new int[n];
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 100);
    for (int i = 0; i < n; i++) {
        arr[i] = distribution(generator);
    }
    return arr;
}

// Function to measure time taken by a function
double measureTime(int* arr, int n) {
    auto start = std::chrono::high_resolution_clock::now();
    // Call the sorting algorithm here (e.g., bubbleSort)
    std::sort(arr, arr + n);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// Bubble sort function
void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Quicksort function
void quicksort(int* arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }
}

// Partition function for quicksort
int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

int main() {
    const int n = 10000; // Size of the array
    int* arr = generateRandomArray(n);

    double bubbleSortTime = measureTime(arr, n);
    bubbleSort(arr, n);

    int* arrCopy = new int[n];
    for (int i = 0; i < n; i++) {
        arrCopy[i] = arr[i];
    }

    double quicksortTime = measureTime(arrCopy, n);
    quicksort(arrCopy, 0, n - 1);

    std::cout << "Bubble sort time: " << bubbleSortTime << " microseconds" << std::endl;
    std::cout << "Quicksort time: " << quicksortTime << " microseconds" << std::endl;

    delete[] arr;
    delete[] arrCopy;

    return 0;
}