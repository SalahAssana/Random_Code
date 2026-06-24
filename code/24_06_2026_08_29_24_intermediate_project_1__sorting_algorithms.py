# Project 1: Sorting Algorithms

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

def selection_sort(arr: List[int]) -> List[int]:
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
    return arr

def insertion_sort(arr: List[int]) -> List[int]:
    n = len(arr)
    for i in range(1, n):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

def quick_sort(arr: List[int]) -> List[int]:
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

def generate_random_array(n: int, min_val: int, max_val: int) -> List[int]:
    return [random.randint(min_val, max_val) for _ in range(n)]

if __name__ == '__main__':
    n = 100
    min_val = 1
    max_val = 100

    arr = generate_random_array(n, min_val, max_val)

    print("Original array:", arr)
    print()

    start_time = time.time()
    bubble_sort_result = bubble_sort(arr.copy())
    end_time = time.time()
    print(f"Bubble sort (time: {end_time - start_time:.2f} seconds):", bubble_sort_result)
    print()

    start_time = time.time()
    selection_sort_result = selection_sort(arr.copy())
    end_time = time.time()
    print(f"Selection sort (time: {end_time - start_time:.2f} seconds):", selection_sort_result)
    print()

    start_time = time.time()
    insertion_sort_result = insertion_sort(arr.copy())
    end_time = time.time()
    print(f"Insertion sort (time: {end_time - start_time:.2f} seconds):", insertion_sort_result)
    print()

    start_time = time.time()
    quick_sort_result = quick_sort(arr.copy())
    end_time = time.time()
    print(f"Quick sort (time: {end_time - start_time:.2f} seconds):", quick_sort_result)
    print()