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

if __name__ == '__main__':
    size = 10000
    max_value = 100

    print("Generating random array of size", size)
    arr = generate_random_array(size, max_value)

    print("\nSorting using Bubble Sort...")
    start_time = time.time()
    sorted_arr_bubble = bubble_sort(arr.copy())
    end_time = time.time()
    print(f"Time taken: {end_time - start_time} seconds")

    print("\nSorting using QuickSort...")
    start_time = time.time()
    sorted_arr_quicksort = quicksort(arr.copy())
    end_time = time.time()
    print(f"Time taken: {end_time - start_time} seconds")

    if sorted_arr_bubble == sorted_arr_quicksort:
        print("Sorted arrays match!")
    else:
        print("Sorting algorithms produced different results!")