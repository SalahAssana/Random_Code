#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

// Function to generate random numbers
void generateRandomNumbers(std::vector<int>& numbers) {
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < numbers.size(); i++) {
        numbers[i] = rand() % 100;
    }
}

// Function to visualize the sorting process
void visualizeSorting(const std::string& algorithm, const std::vector<int>& unsorted, const std::vector<int>& sorted) {
    for (int i = 0; i < unsorted.size(); i++) {
        if (i < sorted.size()) {
            std::cout << unsorted[i] << " ";
        } else {
            std::cout << "* ";
        }
    }
    std::cout << "\n" << algorithm << " sorting completed.\n";
}

// Function to bubble sort the numbers
void bubbleSort(std::vector<int>& numbers) {
    for (int i = 0; i < numbers.size() - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < numbers.size() - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                std::swap(numbers[j], numbers[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Function to quicksort the numbers
void quicksort(std::vector<int>& numbers, int low, int high) {
    if (low >= high) return;
    int pivotIndex = (low + high) / 2;
    std::swap(numbers[low], numbers[pivotIndex]);
    int i = low + 1;
    int j = high;
    while (i <= j) {
        while (i <= j && numbers[i] < numbers[low]) i++;
        while (i <= j && numbers[j] > numbers[low]) j--;
        if (i <= j) std::swap(numbers[i], numbers[j]);
    }
    std::swap(numbers[low], numbers[--j]);
    quicksort(numbers, low, j);
    quicksort(numbers, i, high);
}

int main() {
    // Generate random numbers
    std::vector<int> numbers(10);
    generateRandomNumbers(numbers);

    // Sort using bubble sort and visualize the process
    std::cout << "Bubble sorting...\n";
    bubbleSort(numbers);
    visualizeSorting("Bubble", numbers, numbers);

    // Reset the numbers for quicksort
    numbers = {1, 3, 9, 2, 5, 7, 6, 8, 4, 10};
    std::cout << "Quicksorting...\n";
    quicksort(numbers, 0, numbers.size() - 1);
    visualizeSorting("Quick", numbers, numbers);

    return 0;
}