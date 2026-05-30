#include <iostream>
#include <vector>

// Function to merge two subarrays into one sorted array
std::vector<int> merge(std::vector<int>& left, std::vector<int>& right) {
    std::vector<int> result;
    int i = 0; // Index for the left subarray
    int j = 0; // Index for the right subarray

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            result.push_back(left[i]);
            i++;
        } else {
            result.push_back(right[j]);
            j++;
        }
    }

    // Append any remaining elements from the left or right subarrays
    while (i < left.size()) {
        result.push_back(left[i]);
        i++;
    }
    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }

    return result;
}

// Function to sort an array using merge sort algorithm
std::vector<int> mergeSort(std::vector<int>& arr) {
    if (arr.size() <= 1) {
        return arr; // Base case: already sorted
    }

    int mid = arr.size() / 2;
    std::vector<int> left(arr.begin(), arr.begin() + mid);
    std::vector<int> right(arr.begin() + mid, arr.end());

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

int main() {
    std::vector<int> arr = {5, 2, 8, 3, 1, 6, 4};
    arr = mergeSort(arr);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}