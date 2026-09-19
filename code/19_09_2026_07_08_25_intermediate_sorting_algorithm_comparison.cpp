#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

// Function to generate random numbers
void generateRandomNumbers(vector<int>& arr) {
    for(int i = 0; i < arr.size(); i++) {
        arr[i] = rand() % 100;
    }
}

// Bubble sort algorithm
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// Quick sort algorithm
void quickSort(vector<int>& arr, int low, int high) {
    if(low >= high)
        return;
    int pivot = partition(arr, low, high);
    quickSort(arr, low, pivot-1);
    quickSort(arr, pivot+1, high);
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for(int j = low; j <= high - 1; j++) {
        if(arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Insertion sort algorithm
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i-1;
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int main() {
    // Generate random numbers
    vector<int> arr(10000);
    generateRandomNumbers(arr);

    // Measure time complexity of each sorting algorithm
    auto start = chrono::high_resolution_clock::now();
    bubbleSort(arr.copy());
    auto end = chrono::high_resolution_clock::now();
    double bubbleTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);
    end = chrono::high_resolution_clock::now();
    double quickTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    start = chrono::high_resolution_clock::now();
    insertionSort(arr);
    end = chrono::high_resolution_clock::now();
    double insertTime = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Print time complexity
    cout << "Bubble sort: " << bubbleTime << " microseconds" << endl;
    cout << "Quick sort: " << quickTime << " microseconds" << endl;
    cout << "Insertion sort: " << insertTime << " microseconds" << endl;

    return 0;
}