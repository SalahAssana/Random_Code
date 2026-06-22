#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate random integers for testing
int* generateRandomArray(int n) {
    int* arr = (int*)malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
    return arr;
}

// QuickSort algorithm
void quicksort(int* arr, int low, int high) {
    if (low >= high)
        return;

    int pivot = partition(arr, low, high);

    quicksort(arr, low, pivot-1);
    quicksort(arr, pivot+1, high);
}

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// MergeSort algorithm
void mergeSort(int* arr, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid+1, high);

        merge(arr, low, mid, high);
    }
}

void merge(int* arr, int low, int mid, int high) {
    int i = low;
    int j = mid + 1;
    int k = low;

    int temp[high-low+1];
    while (i <= mid && j <= high) {
        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= high) {
        temp[k++] = arr[j++];
    }

    for (int i = low; i <= high; i++) {
        arr[i] = temp[i];
    }
}

// Function to test and compare sorting algorithms
void sortAndTest(int* arr, int n) {
    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    clock_t start, end;
    double time;

    // QuickSort
    start = clock();
    quicksort(arr, 0, n-1);
    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Quicksort time: %.2f seconds\n", time);

    // MergeSort
    start = clock();
    mergeSort(arr, 0, n-1);
    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("MergeSort time: %.2f seconds\n", time);
}

int main() {
    int n = 10000;
    int* arr = generateRandomArray(n);

    sortAndTest(arr, n);

    free(arr);

    return 0;
}