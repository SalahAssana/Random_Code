#include <iostream>
#include <vector>

// Function to swap two elements in an array
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Selection sort function
void selectionSort(std::vector<int>& grades) {
    for (int i = 0; i < grades.size() - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < grades.size(); j++) {
            if (grades[j] > grades[minIndex]) {
                minIndex = j;
            }
        }
        swap(&grades[i], &grades[minIndex]);
    }
}

// Function to print the array
void printArray(const std::vector<int>& grades) {
    for (int i = 0; i < grades.size(); i++) {
        std::cout << grades[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Synthetic data: student grades array
    std::vector<int> studentsGrades = {85, 90, 78, 92, 88, 76, 95};

    // Print the original array
    std::cout << "Original Grades: ";
    printArray(studentsGrades);

    // Sort the array using selection sort algorithm
    selectionSort(studentsGrades);

    // Print the sorted array
    std::cout << "Sorted Grades (Descending): ";
    printArray(studentsGrades);

    return 0;
}