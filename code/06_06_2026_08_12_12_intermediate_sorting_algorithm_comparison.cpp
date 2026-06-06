#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

// Function to generate random integers
vector<int> generateRandomArray(int n) {
    vector<int> arr;
    default_random_engine eng;
    uniform_int_distribution<> dis(1, 100);
    
    for (int i = 0; i < n; ++i) {
        arr.push_back(dis(eng));
    }
    
    return arr;
}

// Bubble sort algorithm
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// Selection sort algorithm
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Insertion sort algorithm
void insertionSort(vector<int>& arr) {
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

int main() {
    const int n = 10000; // Size of the array
    
    vector<int> randomArray = generateRandomArray(n);
    
    cout << "Unsorted array: ";
    for (int i : randomArray)
        cout << i << " ";
    cout << endl;
    
    auto startBubble = chrono::high_resolution_clock::now();
    bubbleSort(randomArray.copy());
    auto endBubble = chrono::high_resolution_clock::now();
    cout << "Sorted by Bubble sort: ";
    for (int i : randomArray)
        cout << i << " ";
    cout << endl;
    
    cout << "Time taken by Bubble sort: "
         << chrono::duration_cast<chrono::microseconds>(endBubble - startBubble).count() << " microseconds" << endl;
    
    auto startSelection = chrono::high_resolution_clock::now();
    selectionSort(randomArray.copy());
    auto endSelection = chrono::high_resolution_clock::now();
    cout << "Sorted by Selection sort: ";
    for (int i : randomArray)
        cout << i << " ";
    cout << endl;
    
    cout << "Time taken by Selection sort: "
         << chrono::duration_cast<chrono::microseconds>(endSelection - startSelection).count() << " microseconds" << endl;
    
    auto startInsertion = chrono::high_resolution_clock::now();
    insertionSort(randomArray.copy());
    auto endInsertion = chrono::high_resolution_clock::now();
    cout << "Sorted by Insertion sort: ";
    for (int i : randomArray)
        cout << i << " ";
    cout << endl;
    
    cout << "Time taken by Insertion sort: "
         << chrono::duration_cast<chrono::microseconds>(endInsertion - startInsertion).count() << " microseconds" << endl;
    
    return 0;
}