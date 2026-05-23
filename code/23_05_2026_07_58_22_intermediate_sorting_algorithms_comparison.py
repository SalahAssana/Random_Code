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
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

def generate_random_array(size: int, max_val: int) -> List[int]:
    return [random.randint(0, max_val) for _ in range(size)]

if __name__ == '__main__':
    size = 10000
    max_val = 100000
    arrays = [
        generate_random_array(size, max_val),
        generate_random_array(size, max_val),
        generate_random_array(size, max_val)
    ]
    
    start_time = time.time()
    for i in range(3):
        print(f"Sorting array {i+1} using bubble sort...")
        arrays[i] = bubble_sort(arrays[i])
    end_time = time.time()
    print(f"Bubble sort took {end_time - start_time:.2f} seconds.")
    
    start_time = time.time()
    for i in range(3):
        print(f"Sorting array {i+1} using selection sort...")
        arrays[i] = selection_sort(arrays[i])
    end_time = time.time()
    print(f"Selection sort took {end_time - start_time:.2f} seconds.")
    
    start_time = time.time()
    for i in range(3):
        print(f"Sorting array {i+1} using insertion sort...")
        arrays[i] = insertion_sort(arrays[i])
    end_time = time.time()
    print(f"Insertion sort took {end_time - start_time:.2f} seconds.")