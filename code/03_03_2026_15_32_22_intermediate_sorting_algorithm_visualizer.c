#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define a struct to hold the data for visualization
typedef struct {
    int* arr;
    int n;
} Data;

// Function to generate random array of size 'n'
Data generateRandomArray(int n) {
    Data data = (Data)malloc(sizeof(struct Data));
    data->arr = (int*)malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        data->arr[i] = rand() % 100;
    }
    data->n = n;
    return data;
}

// Function to visualize the array
void visualizeArray(Data data) {
    printf("Visualizing array: ");
    for (int i = 0; i < data->n; i++) {
        printf("%d ", data->arr[i]);
    }
    printf("\n");
}

// Function to perform Bubble Sort
void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to measure the time taken by an algorithm
double measureTime(Data data, void (*func)(int*, int)) {
    clock_t start = clock();
    func(data->arr, data->n);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Main function to visualize and compare the performance of different sorting algorithms
int main() {
    // Generate random array of size 100
    Data data = generateRandomArray(100);

    // Perform Bubble Sort
    bubbleSort(data->arr, data->n);
    printf("Bubble Sort Time: %f seconds\n", measureTime(data, &bubbleSort));

    return 0;
}