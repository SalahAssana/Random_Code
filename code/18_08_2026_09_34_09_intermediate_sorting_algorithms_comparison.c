#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate random array of size n
int* generateRandomArray(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
    return arr;
}

// Function to print array
void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Quick Sort Algorithm
void quickSort(int* arr, int left, int right) {
    if (left < right) {
        int pivotIndex = partition(arr, left, right);
        quickSort(arr, left, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, right);
    }
}

// Partition function for Quick Sort
int partition(int* arr, int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;
    return i + 1;
}

// Merge Sort Algorithm
void mergeSort(int* arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Merge function for Merge Sort
void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* leftArr = (int*)malloc(n1 * sizeof(int));
    int* rightArr = (int*)malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }
    while (i < n1) {
        arr[k++] = leftArr[i++];
    }
    while (j < n2) {
        arr[k++] = rightArr[j++];
    }
    free(leftArr);
    free(rightArr);
}

// Insertion Sort Algorithm
void insertionSort(int* arr, int n) {
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

// Main function
int main() {
    srand(time(NULL));
    int n = 10000;
    int* arr = generateRandomArray(n);
    printf("Original Array: ");
    printArray(arr, n);

    // Quick Sort
    quickSort(arr, 0, n - 1);
    printf("Quick Sort: ");
    printArray(arr, n);

    // Merge Sort
    int* mergeArr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        mergeArr[i] = arr[i];
    }
    mergeSort(mergeArr, 0, n - 1);
    printf("Merge Sort: ");
    printArray(mergeArr, n);
    free(mergeArr);

    // Insertion Sort
    int* insertArr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        insertArr[i] = arr[i];
    }
    insertionSort(insertArr, n);
    printf("Insertion Sort: ");
    printArray(insertArr, n);
    free(insertArr);

    return 0;
}