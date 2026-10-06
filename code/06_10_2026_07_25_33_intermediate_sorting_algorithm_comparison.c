#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define constants for sorting algorithms
#define ALGORITHMS 4
#define NUM_TESTS 5
#define MIN_SIZE 1000
#define MAX_SIZE 50000
#define ITERATIONS 10

// Function prototypes
void sortArray(int*, int, int);
int* generateRandomArray(int, int);
void printArray(int*, int);

int main() {
    // Seed random number generator
    srand(time(NULL));

    // Define array sizes for testing
    int sizes[NUM_TESTS] = {MIN_SIZE, MIN_SIZE * 2, MIN_SIZE * 5, MIN_SIZE * 10, MAX_SIZE};

    // Create a struct to hold data for each algorithm
    typedef struct {
        char* name;
        void (*sortFunction)(int*, int);
    } Algorithm;

    Algorithm algorithms[ALGORITHMS] = {
        {"Bubble Sort", &bubbleSort},
        {"Selection Sort", &selectionSort},
        {"Insertion Sort", &insertionSort},
        {"Quick Sort", &quickSort}
    };

    // Run tests for each algorithm
    for (int i = 0; i < ALGORITHMS; i++) {
        printf("Testing %s...\n", algorithms[i].name);
        for (int j = 0; j < NUM_TESTS; j++) {
            int* array = generateRandomArray(sizes[j], sizes[j]);
            clock_t start = clock();
            for (int k = 0; k < ITERATIONS; k++) {
                algorithms[i].sortFunction(array, sizes[j]);
            }
            clock_t end = clock();
            double time = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Time: %f seconds\n", time);
            printArray(array, sizes[j]);
            free(array);
        }
    }

    return 0;
}

// Sorting functions
void bubbleSort(int* array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int* array, int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        int temp = array[i];
        array[i] = array[minIndex];
        array[minIndex] = temp;
    }
}

void insertionSort(int* array, int size) {
    for (int i = 1; i < size; i++) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void quickSort(int* array, int size) {
    if (size <= 1) return;
    int pivotIndex = size / 2;
    int pivot = array[pivotIndex];
    int left = 0;
    int right = size - 1;

    while (left < right) {
        while (array[left] < pivot) left++;
        while (array[right] > pivot) right--;
        if (left >= right) break;
        int temp = array[left];
        array[left] = array[right];
        array[right] = temp;
        left++;
        right--;
    }

    for (int i = 0; i < size - left; i++) {
        array[i] = array[left + i];
    }
    for (int i = size - left; i < size; i++) {
        array[i] = pivot;
    }

    quickSort(array, size - left);
}

// Utility functions
int* generateRandomArray(int size, int max) {
    int* array = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % max;
    }
    return array;
}

void printArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}