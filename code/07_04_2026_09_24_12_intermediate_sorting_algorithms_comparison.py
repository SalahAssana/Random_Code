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

def compare_sorting_algorithms(arr_size: int, max_value: int):
    arr = generate_random_array(arr_size, max_value)
    
    start_time = time.time()
    bubble_sorted_arr = bubble_sort(arr.copy())
    bubble_time = time.time() - start_time
    
    start_time = time.time()
    quicksorted_arr = quicksort(arr.copy())
    quicksort_time = time.time() - start_time
    
    print(f"Array size: {arr_size}, Max value: {max_value}")
    print(f"Bubble sort took {bubble_time:.6f} seconds")
    print(f"Quicksort took {quicksort_time:.6f} seconds")
    print(f"Bubble sorted array: {bubble_sorted_arr}")
    print(f"Quicksorted array: {quicksorted_arr}\n")

if __name__ == '__main__':
    compare_sorting_algorithms(100, 50)