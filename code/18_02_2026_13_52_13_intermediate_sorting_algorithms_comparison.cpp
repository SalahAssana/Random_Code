#include <iostream>
#include <chrono>
#include <vector>
#include <random>

// Function to generate random array
std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 100);
    
    for (int i = 0; i < size; ++i) {
        arr.push_back(distribution(generator));
    }
    
    return arr;
}

// Function to perform bubble sort
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to perform insertion sort
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
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

void quicksort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Function to perform mergesort
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
    }
    
    int i, j, k;
    i = j = k = 0;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[left + k] = L[i];
            ++i;
        } else {
            arr[left + k] = R[j];
            ++j;
        }
        
        ++k;
    }
    
    while (i < n1) {
        arr[left + k] = L[i];
        ++i;
        ++k;
    }
    
    while (j < n2) {
        arr[left + k] = R[j];
        ++j;
        ++k;
    }
}

void mergesort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}

int main() {
    int size = 10000;
    
    std::vector<int> arr = generateRandomArray(size);
    
    // Measure time for bubble sort
    auto start = std::chrono::high_resolution_clock::now();
    bubbleSort(arr.copy());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Bubble Sort Time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds" << std::endl;
    
    // Measure time for insertion sort
    start = std::chrono::high_resolution_clock::now();
    insertionSort(arr.copy());
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Insertion Sort Time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds" << std::endl;
    
    // Measure time for quicksort
    start = std::chrono::high_resolution_clock::now();
    quicksort(arr, 0, size - 1);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Quicksort Time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds" << std::endl;
    
    // Measure time for mergesort
    start = std::chrono::high_resolution_clock::now();
    mergesort(arr, 0, size - 1);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Mergesort Time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseconds" << std::endl;
    
    return 0;
}