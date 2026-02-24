# Efficient Sorting Algorithm

import random
import time
from typing import List

def insertion_sort(arr: List[int]) -> List[int]:
    """Insertion sort algorithm"""
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

def merge_sort(arr: List[int]) -> List[int]:
    """Merge sort algorithm"""
    if len(arr) <= 1:
        return arr
    
    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]
    
    left_half = merge_sort(left_half)
    right_half = merge_sort(right_half)
    
    return merge(left_half, right_half)

def merge(left: List[int], right: List[int]) -> List[int]:
    """Merge two sorted lists"""
    merged = []
    left_index = 0
    right_index = 0
    
    while left_index < len(left) and right_index < len(right):
        if left[left_index] <= right[right_index]:
            merged.append(left[left_index])
            left_index += 1
        else:
            merged.append(right[right_index])
            right_index += 1
    
    merged.extend(left[left_index:])
    merged.extend(right[right_index:])
    
    return merged

def test_sorting_algorithm(func, arr):
    """Test the sorting algorithm"""
    start_time = time.time()
    sorted_arr = func(arr)
    end_time = time.time()
    
    print(f"Algorithm: {func.__name__}")
    print(f"Input array: {arr}")
    print(f"Sorted array: {sorted_arr}")
    print(f"Time taken: {end_time - start_time} seconds")

def main():
    """Main function"""
    # Generate random input array
    arr = [random.randint(0, 100) for _ in range(10)]
    
    # Sort the array using insertion sort and merge sort algorithms
    insertion_sorted_arr = insertion_sort(arr.copy())
    merge_sorted_arr = merge_sort(arr.copy())
    
    # Test both sorting algorithms
    test_sorting_algorithm(insertion_sort, arr)
    test_sorting_algorithm(merge_sort, arr)

if __name__ == '__main__':
    main()