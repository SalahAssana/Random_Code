#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

// Function to generate random array
std::vector<int> generateArray(int n) {
    std::vector<int> arr;
    for (int i = 0; i < n; ++i) {
        arr.push_back(rand() % 100);
    }
    return arr;
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
        if (!swapped) break;
    }
}

// Quick sort function
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low >= high) return;
    int pivotIndex = partition(arr, low, high);
    quickSort(arr, low, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, high);
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Merge sort function
void mergeSort(std::vector<int>& arr, int low, int high) {
    if (low >= high) return;
    int mid = (low + high) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

void merge(std::vector<int>& arr, int low, int mid, int high) {
    std::vector<int> leftArr;
    std::vector<int> rightArr;
    for (int i = low; i <= mid; ++i) {
        leftArr.push_back(arr[i]);
    }
    for (int i = mid + 1; i <= high; ++i) {
        rightArr.push_back(arr[i]);
    }
    int i = 0, j = 0;
    int k = low;
    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }
    while (i < leftArr.size()) {
        arr[k++] = leftArr[i++];
    }
    while (j < rightArr.size()) {
        arr[k++] = rightArr[j++];
    }
}

int main() {
    srand(time(0));
    
    int n;
    std::cout << "Enter the size of the array: ";
    std::cin >> n;

    // Generate random array
    std::vector<int> arr = generateArray(n);

    // Bubble sort
    clock_t startBubble = clock();
    bubbleSort(arr);
    clock_t endBubble = clock();
    double timeBubble = (double)(endBubble - startBubble) / CLOCKS_PER_SEC;
    std::cout << "Bubble sort took: " << timeBubble << " seconds." << std::endl;

    // Quick sort
    quickSort(arr, 0, n - 1);
    
    clock_t startQuick = clock();
    quickSort(arr, 0, n - 1);
    clock_t endQuick = clock();
    double timeQuick = (double)(endQuick - startQuick) / CLOCKS_PER_SEC;
    std::cout << "Quick sort took: " << timeQuick << " seconds." << std::endl;

    // Merge sort
    mergeSort(arr, 0, n - 1);
    
    clock_t startMerge = clock();
    mergeSort(arr, 0, n - 1);
    clock_t endMerge = clock();
    double timeMerge = (double)(endMerge - startMerge) / CLOCKS_PER_SEC;
    std::cout << "Merge sort took: " << timeMerge << " seconds." << std::endl;

    return 0;
}