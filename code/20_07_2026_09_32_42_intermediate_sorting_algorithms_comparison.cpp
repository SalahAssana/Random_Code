#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

// Function to perform bubble sort on an array of integers
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to perform selection sort on an array of integers
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Swap elements
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

// Function to perform insertion sort on an array of integers
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            // Shift elements to the right
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    const int N = 10000; // Size of the array
    std::vector<int> data(N); // Initialize with random values

    for (int i = 0; i < N; i++) {
        data[i] = rand() % 100; // Randomly generate numbers from 0 to 99
    }

    int arr[N]; // Copy the data into a regular array
    std::copy(data.begin(), data.end(), arr);

    // Measure time for bubble sort
    auto start1 = std::chrono::high_resolution_clock::now();
    bubbleSort(arr, N);
    auto end1 = std::chrono::high_resolution_clock::now();

    // Measure time for selection sort
    auto start2 = std::chrono::high_resolution_clock::now();
    selectionSort(arr, N);
    auto end2 = std::chrono::high_resolution_clock::now();

    // Measure time for insertion sort
    auto start3 = std::chrono::high_resolution_clock::now();
    insertionSort(arr, N);
    auto end3 = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time for each sorting algorithm
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3);

    // Print the elapsed time for each sorting algorithm
    std::cout << "Bubble Sort: " << duration1.count() << " microseconds" << std::endl;
    std::cout << "Selection Sort: " << duration2.count() << " microseconds" << std::endl;
    std::cout << "Insertion Sort: " << duration3.count() << " microseconds" << std::endl;

    return 0;
}