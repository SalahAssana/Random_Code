#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

// Function to generate random array of size n
std::vector<int> generateArray(int n) {
    std::vector<int> arr;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 100);

    for (int i = 0; i < n; ++i) {
        arr.push_back(distribution(generator));
    }

    return arr;
}

// Quicksort algorithm
void quicksort(std::vector<int>& arr, int low, int high) {
    if (low >= high)
        return;

    int pivotIndex = partition(arr, low, high);

    quicksort(arr, low, pivotIndex - 1);
    quicksort(arr, pivotIndex + 1, high);
}

// Partition function for quicksort
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Mergesort algorithm
void mergesort(std::vector<int>& arr, int low, int high) {
    if (low >= high)
        return;

    int mid = (low + high) / 2;

    mergesort(arr, low, mid);
    mergesort(arr, mid + 1, high);

    merge(arr, low, mid, high);
}

// Merge function for mergesort
void merge(std::vector<int>& arr, int low, int mid, int high) {
    int left = low;
    int right = mid + 1;

    std::vector<int> temp(high - low + 1);

    while (left <= mid && right <= high) {
        if (arr[left] < arr[right]) {
            temp[low++] = arr[left++];
        } else {
            temp[low++] = arr[right++];
        }
    }

    while (left <= mid) {
        temp[low++] = arr[left++];
    }

    while (right <= high) {
        temp[low++] = arr[right++];
    }

    for (int i = low; i < high + 1; ++i) {
        arr[i] = temp[i - low];
    }
}

// Function to test and compare sorting algorithms
void testSortingAlgorithms() {
    int n;
    std::cout << "Enter the size of the array: ";
    std::cin >> n;

    std::vector<int> arr = generateArray(n);

    std::cout << "Original array: ";
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Quicksort
    int lowQuicksort = 0;
    int highQuicksort = n - 1;
    quicksort(arr, lowQuicksort, highQuicksort);

    std::cout << "Quicksort array: ";
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Mergesort
    int lowMergesort = 0;
    int highMergesort = n - 1;
    mergesort(arr, lowMergesort, highMergesort);

    std::cout << "Mergesort array: ";
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    testSortingAlgorithms();
    return 0;
}