#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

// Function to print the array
void printArray(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Bubble Sort function
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// Quick Sort function
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Function to compare the performance of different algorithms
void comparePerformance() {
    vector<int> arr = {4, 2, 9, 6, 5, 1, 3, 7, 8};

    // Measure time for bubble sort
    auto start = chrono::high_resolution_clock().now();
    bubbleSort(arr);
    auto end = chrono::high_resolution_clock().now();

    cout << "Bubble Sort: ";
    printArray(arr);

    double bubbleTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Time taken by Bubble Sort: " << bubbleTime << " microseconds" << endl;

    // Measure time for quick sort
    arr = {4, 2, 9, 6, 5, 1, 3, 7, 8};
    start = chrono::high_resolution_clock().now();
    quickSort(arr, 0, arr.size() - 1);
    end = chrono::high_resolution_clock().now();

    cout << "Quick Sort: ";
    printArray(arr);

    double quickTime = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Time taken by Quick Sort: " << quickTime << " microseconds" << endl;
}

int main() {
    comparePerformance();
    return 0;
}