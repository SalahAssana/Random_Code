#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

// Structure to hold sorting algorithm information
struct SortingAlgorithm {
    std::string name;
    void (*sortFunction)(int*, int);
};

void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

void mergeSort(int* arr, int n) {
    if (n < 2)
        return;

    int mid = n / 2;
    std::vector<int> left(arr, arr + mid);
    std::vector<int> right(arr + mid, arr + n);

    mergeSort(left.data(), left.size());
    mergeSort(right.data(), right.size());

    int i = 0, j = 0, k = 0;

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    while (i < left.size())
        arr[k++] = left[i++];

    while (j < right.size())
        arr[k++] = right[j++];
}

void quickSort(int* arr, int n) {
    if (n < 2)
        return;

    int pivotIndex = rand() % n;
    std::swap(arr[pivotIndex], arr[n - 1]);

    int i = 0, j = n - 2;

    while (i < j) {
        if (arr[i] > arr[j])
            std::swap(arr[i], arr[j]);
        ++i;
        --j;
    }

    if (rand() % 2)
        quickSort(&arr[1], j);
    else
        quickSort(&arr[1], i);

    quickSort(&arr[i + 1], n - i - 1);
}

void displayArray(int* arr, int n) {
    for (int i = 0; i < n; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

int main() {
    srand(time(0));

    const int N = 10;
    int array[N];
    for (int i = 0; i < N; ++i) {
        array[i] = rand() % 100;
    }

    SortingAlgorithm algorithms[] = {
        {"Bubble Sort", bubbleSort},
        {"Merge Sort", mergeSort},
        {"Quick Sort", quickSort}
    };

    std::cout << "Original Array: ";
    displayArray(array, N);

    for (int i = 0; i < sizeof(algorithms) / sizeof(SortingAlgorithm); ++i) {
        int* arr = array;
        algorithms[i].sortFunction(arr, N);
        std::cout << "Sorted by " << algorithms[i].name << ": ";
        displayArray(array, N);
    }

    return 0;
}