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

// Bubble sort function
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
        if (!swapped) break;
    }
}

// Selection sort function
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Insertion sort function
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    vector<int> arr(10000);
    for (int i = 0; i < 10000; i++) {
        arr[i] = rand() % 10000;
    }

    // Test bubble sort
    auto startBubble = chrono::high_resolution_clock::now();
    bubbleSort(arr.copy());
    auto endBubble = chrono::high_resolution_clock::now();
    cout << "Time taken by Bubble Sort: "
         << chrono::duration_cast<chrono::microseconds>(endBubble - startBubble).count()
         << " microseconds" << endl;
    printArray(arr);

    // Test selection sort
    vector<int> arr2 = arr;
    auto startSelection = chrono::high_resolution_clock::now();
    selectionSort(arr2);
    auto endSelection = chrono::high_resolution_clock::now();
    cout << "Time taken by Selection Sort: "
         << chrono::duration_cast<chrono::microseconds>(endSelection - startSelection).count()
         << " microseconds" << endl;
    printArray(arr2);

    // Test insertion sort
    vector<int> arr3 = arr;
    auto startInsertion = chrono::high_resolution_clock::now();
    insertionSort(arr3);
    auto endInsertion = chrono::high_resolution_clock::now();
    cout << "Time taken by Insertion Sort: "
         << chrono::duration_cast<chrono::microseconds>(endInsertion - startInsertion).count()
         << " microseconds" << endl;
    printArray(arr3);

    return 0;
}