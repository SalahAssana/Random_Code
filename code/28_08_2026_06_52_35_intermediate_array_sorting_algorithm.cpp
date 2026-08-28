#include <iostream>
#include <algorithm>
#include <vector>

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

// Function to perform quick sort
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low >= high)
        return;
    int i = low, j = high;
    int pivot = arr[(i + j) / 2];
    while (1) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++; j--;
        } else
            break;
    }
    quickSort(arr, low, j);
    quickSort(arr, i, high);
}

// Function to perform merge sort
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Function to perform the merge operation
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int len1 = mid - left + 1;
    int len2 = right - mid;
    std::vector<int> leftHalf(len1), rightHalf(len2);
    for (int i = 0; i < len1; i++)
        leftHalf[i] = arr[left + i];
    for (int j = 0; j < len2; j++)
        rightHalf[j] = arr[mid + 1 + j];
    int k = left;
    int i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (leftHalf[i] <= rightHalf[j]) {
            arr[k++] = leftHalf[i++];
        } else {
            arr[k++] = rightHalf[j++];
        }
    }
    while (i < len1) {
        arr[k++] = leftHalf[i++];
    }
    while (j < len2) {
        arr[k++] = rightHalf[j++];
    }
}

int main() {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    // Perform bubble sort
    std::cout << "Original array: ";
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    bubbleSort(arr);
    std::cout << "After bubble sort: ";
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // Perform quick sort
    int low = 0, high = arr.size() - 1;
    quickSort(arr, low, high);
    std::cout << "After quick sort: ";
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // Perform merge sort
    mergeSort(arr, 0, arr.size() - 1);
    std::cout << "After merge sort: ";
    for (int i : arr) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    
    return 0;
}