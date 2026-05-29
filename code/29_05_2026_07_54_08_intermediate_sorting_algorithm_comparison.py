# Sorting Algorithm Comparison

import random
import time
from typing import List

def bubble_sort(arr: List[int]) -> List[int]:
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr

def quicksort(arr: List[int]) -> List[int]:
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quicksort(left) + middle + quicksort(right)

def generate_random_array(size: int, max_value: int) -> List[int]:
    return [random.randint(0, max_value) for _ in range(size)]

def main():
    sizes = [100, 500, 1000]
    max_values = [10, 50, 100]

    for size in sizes:
        for max_value in max_values:
            random_array = generate_random_array(size, max_value)
            print(f"Sorting {size} integers with maximum value of {max_value}:")
            start_time = time.time()
            bubble_sorted = bubble_sort(random_array.copy())
            end_time = time.time()
            print(f"Bubble sort: {end_time - start_time:.4f} seconds")
            print("Sorted array:", bubble_sorted)
            print()

            random_array = generate_random_array(size, max_value)
            print(f"Sorting {size} integers with maximum value of {max_value}:")
            start_time = time.time()
            quicksorted = quicksort(random_array.copy())
            end_time = time.time()
            print(f"Quicksort: {end_time - start_time:.4f} seconds")
            print("Sorted array:", quicksorted)
            print()

if __name__ == '__main__':
    main()