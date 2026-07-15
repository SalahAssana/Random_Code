#include <iostream>
#include <ctime>
#include <cstdlib>

// Structure to represent an integer along with its original index
struct Data {
    int value;
    int origin;
};

// Function to perform bubble sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// Function to perform insertion sort
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

// Function to perform quicksort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

// Function to perform partition in quicksort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Function to generate random array of integers
Data* generateRandomArray(int n, int max) {
    Data* arr = new Data[n];
    for (int i = 0; i < n; ++i) {
        arr[i].value = rand() % max;
        arr[i].origin = i;
    }
    return arr;
}

// Function to test the efficiency of sorting algorithms
void testEfficiency(int n, int max) {
    Data* arr = generateRandomArray(n, max);
    
    // Measure time for bubble sort
    clock_t startBubble = clock();
    bubbleSort(arr[0].value, n);
    double timeBubble = (double)(clock() - startBubble) / CLOCKS_PER_SEC;
    
    // Measure time for insertion sort
    clock_t startInsertion = clock();
    insertionSort(arr[0].value, n);
    double timeInsertion = (double)(clock() - startInsertion) / CLOCKS_PER_SEC;
    
    // Measure time for quicksort
    clock_t startQuicksort = clock();
    quickSort(arr[0].value, 0, n - 1);
    double timeQuicksort = (double)(clock() - startQuicksort) / CLOCKS_PER_SEC;
    
    std::cout << "Time taken by bubble sort: " << timeBubble << " seconds" << std::endl;
    std::cout << "Time taken by insertion sort: " << timeInsertion << " seconds" << std::endl;
    std::cout << "Time taken by quicksort: " << timeQuicksort << " seconds" << std::endl;
}

int main() {
    int n = 1000; // Size of the array
    int max = 10000; // Maximum value in the array
    
    testEfficiency(n, max);
    
    return 0;
}