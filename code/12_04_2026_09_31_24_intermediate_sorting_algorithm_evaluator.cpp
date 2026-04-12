#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

// Function to generate random integers for testing
std::vector<int> generateRandomIntegers(int size) {
    std::vector<int> result(size);
    for (int i = 0; i < size; ++i) {
        result[i] = rand() % 100;
    }
    return result;
}

// QuickSort function
void quicksort(std::vector<int>& arr, int low, int high) {
    if (low >= high) return;

    int pivotIndex = partition(arr, low, high);
    quicksort(arr, low, pivotIndex-1);
    quicksort(arr, pivotIndex+1, high);
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

    std::swap(arr[i+1], arr[high]);
    return i + 1;
}

// MergeSort function
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);

        merge(arr, left, mid, right);
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> leftHalf(n1), rightHalf(n2);

    for (int i = 0; i < n1; ++i) {
        leftHalf[i] = arr[left+i];
    }

    for (int i = 0; i < n2; ++i) {
        rightHalf[i] = arr[mid+1+i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftHalf[i] <= rightHalf[j]) {
            arr[k++] = leftHalf[i++];
        } else {
            arr[k++] = rightHalf[j++];
        }
    }

    while (i < n1) {
        arr[k++] = leftHalf[i++];
    }

    while (j < n2) {
        arr[k++] = rightHalf[j++];
    }
}

// Main function
int main() {
    srand(time(0)); // seed random number generator

    int size = 10000; // size of the array to be sorted
    std::vector<int> randomIntegers = generateRandomIntegers(size);

    auto start = std::chrono::high_resolution_clock::now();

    quicksort(randomIntegers, 0, size-1);

    auto stop = std::chrono::high_resolution_clock::now();
    double timeTaken = std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count() / 1000000.0;

    std::cout << "Quicksort took " << timeTaken << " seconds.\n";

    start = std::chrono::high_resolution_clock::now();

    mergeSort(randomIntegers, 0, size-1);

    stop = std::chrono::high_resolution_clock::now();
    timeTaken = std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count() / 1000000.0;

    std::cout << "Merge sort took " << timeTaken << " seconds.\n";

    return 0;
}