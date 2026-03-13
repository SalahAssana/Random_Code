#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000
#define MIN_SIZE 10
#define NUM_TESTS 5
#define ALGO_COUNT 4

// Function prototypes
void swap(int* a, int* b);
void insertionSort(int* arr, int n);
void bubbleSort(int* arr, int n);
void selectionSort(int* arr, int n);
void quickSort(int* arr, int low, int high);

int main() {
    // Seed random number generator
    srand(time(NULL));

    // Test size array
    int testSizes[NUM_TESTS] = {MIN_SIZE, MAX_SIZE / 2, MAX_SIZE - MIN_SIZE, (MAX_SIZE + MIN_SIZE) / 2, MAX_SIZE};

    // Algorithm names
    char* algoNames[ALGO_COUNT] = {"Insertion Sort", "Bubble Sort", "Selection Sort", "Quick Sort"};

    // Test each algorithm for each test size
    for (int i = 0; i < NUM_TESTS; i++) {
        int n = testSizes[i];
        int* arr = (int*)malloc(n * sizeof(int));

        // Generate random array
        for (int j = 0; j < n; j++)
            arr[j] = rand() % 100;

        printf("Testing with size %d...\n", n);

        // Run each algorithm and measure time
        double times[ALGO_COUNT];
        for (int k = 0; k < ALGO_COUNT; k++) {
            clock_t start, end;
            start = clock();
            switch (k) {
                case 0:
                    insertionSort(arr, n);
                    break;
                case 1:
                    bubbleSort(arr, n);
                    break;
                case 2:
                    selectionSort(arr, n);
                    break;
                case 3:
                    quickSort(arr, 0, n - 1);
                    break;
            }
            end = clock();
            times[k] = (double)(end - start) / CLOCKS_PER_SEC;
        }

        // Print results
        for (int k = 0; k < ALGO_COUNT; k++)
            printf("%s: %f seconds\n", algoNames[k], times[k]);

        free(arr);
    }

    return 0;
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void insertionSort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
            swap(&arr[j + 1], &arr[j--]);

        arr[++j] = key;
    }
}

void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

void selectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;

        swap(&arr[i], &arr[minIndex]);
    }
}

void quickSort(int* arr, int low, int high) {
    if (low >= high)
        return;
    int pivot = (low + high) / 2;
    int i = low, j = high;

    while (1) {
        while (arr[i] < arr[pivot])
            i++;
        while (arr[j] > arr[pivot])
            j--;

        if (i >= j)
            return;

        swap(&arr[i], &arr[j]);
        i++;
        j--;
    }
}