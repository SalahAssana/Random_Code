#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

// Function to perform Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to perform Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Function to perform Merge Sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Function to merge two sorted subarrays
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

// Function to generate random array
std::vector<int> generateRandomArray(int size, int maxVal) {
    std::vector<int> arr;
    for (int i = 0; i < size; ++i) {
        arr.push_back(rand() % maxVal);
    }
    return arr;
}

// Main function to test and compare the sorting algorithms
int main() {
    const int arraySize = 10000;
    const int maxValue = 100000;

    std::vector<int> bubbleSortArray = generateRandomArray(arraySize, maxValue);
    int* bubbleSortArr = new int[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        bubbleSortArr[i] = bubbleSortArray[i];
    }

    auto startBubbleSort = std::chrono::high_resolution_clock::now();
    bubbleSort(bubbleSortArr, arraySize);
    auto endBubbleSort = std::chrono::high_resolution_clock::now();

    delete[] bubbleSortArr;

    std::vector<int> insertionSortArray = generateRandomArray(arraySize, maxValue);
    int* insertionSortArr = new int[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        insertionSortArr[i] = insertionSortArray[i];
    }

    auto startInsertionSort = std::chrono::high_resolution_clock::now();
    insertionSort(insertionSortArr, arraySize);
    auto endInsertionSort = std::chrono::high_resolution_clock::now();

    delete[] insertionSortArr;

    std::vector<int> mergeSortArray = generateRandomArray(arraySize, maxValue);

    int* mergeSortArr = new int[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        mergeSortArr[i] = mergeSortArray[i];
    }

    auto startMergeSort = std::chrono::high_resolution_clock::now();
    mergeSort(mergeSortArr, 0, arraySize - 1);
    auto endMergeSort = std::chrono::high_resolution_clock::now();

    delete[] mergeSortArr;

    std::cout << "Bubble Sort time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(endBubbleSort - startBubbleSort).count()
              << " microseconds" << std::endl;
    std::cout << "Insertion Sort time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(endInsertionSort - startInsertionSort).count()
              << " microseconds" << std::endl;
    std::cout << "Merge Sort time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(endMergeSort - startMergeSort).count()
              << " microseconds" << std::endl;

    return 0;
}