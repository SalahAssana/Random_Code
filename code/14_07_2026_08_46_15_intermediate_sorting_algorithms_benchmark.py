import time
import random
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

def benchmark_sorting_algorithm(algorithm, size):
    array = [random.randint(0, 100000) for _ in range(size)]
    start_time = time.time()
    sorted_array = algorithm(array)
    end_time = time.time()
    print(f"Sorting {size} elements using {algorithm.__name__}:")
    print(f"Time taken: {end_time - start_time:.4f} seconds")
    return sorted_array

if __name__ == '__main__':
    sizes = [100, 500, 1000]
    for size in sizes:
        print(f"Benchmarking with array of size {size}:")
        bubble_sort(benchmark_sorting_algorithm(bubble_sort, size))
        quicksort(benchmark_sorting_algorithm(quicksort, size))