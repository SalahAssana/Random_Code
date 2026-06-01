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

def compare_sorting_algorithms(algorithm_name: str, array: List[int]) -> None:
    start_time = time.time()
    sorted_array = eval(f"{algorithm_name}_sort(array)")
    end_time = time.time()
    print(f"Sorted {array} using {algorithm_name}: {end_time - start_time:.2f} seconds")

def main() -> None:
    array_size = 1000
    max_value = 10000
    random_array = generate_random_array(array_size, max_value)

    print("Bubble Sort:")
    compare_sorting_algorithms("bubble", random_array.copy())

    print("\nQuicksort:")
    compare_sorting_algorithms("quicksort", random_array.copy())

if __name__ == '__main__':
    main()