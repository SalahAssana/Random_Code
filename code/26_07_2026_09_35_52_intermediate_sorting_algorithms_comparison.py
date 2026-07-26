import random
import time
from typing import List

def bubble_sort(arr: List[int]) -> None:
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

def insertion_sort(arr: List[int]) -> None:
    n = len(arr)
    for i in range(1, n):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

def selection_sort(arr: List[int]) -> None:
    n = len(arr)
    for i in range(n):
        min_index = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_index]:
                min_index = j
        arr[i], arr[min_index] = arr[min_index], arr[i]

def quick_sort(arr: List[int]) -> None:
    if len(arr) <= 1:
        return
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    quick_sort(left)
    quick_sort(right)
    arr.clear()
    arr.extend(middle)
    arr.extend(left)
    arr.extend(right)

def merge_sort(arr: List[int]) -> None:
    if len(arr) <= 1:
        return
    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]
    merge_sort(left_half)
    merge_sort(right_half)
    i = j = k = 0
    while i < len(left_half) and j < len(right_half):
        if left_half[i] <= right_half[j]:
            arr[k] = left_half[i]
            i += 1
        else:
            arr[k] = right_half[j]
            j += 1
        k += 1
    while i < len(left_half):
        arr[k] = left_half[i]
        i += 1
        k += 1
    while j < len(right_half):
        arr[k] = right_half[j]
        j += 1
        k += 1

def generate_random_array(n: int, min_val: int, max_val: int) -> List[int]:
    return [random.randint(min_val, max_val) for _ in range(n)]

if __name__ == '__main__':
    n = 1000
    min_val = 0
    max_val = 1000
    array_size = len(generate_random_array(n, min_val, max_val))
    print(f"Generating random array of size {array_size}...")
    arr = generate_random_array(array_size, min_val, max_val)
    print("Sorting algorithms comparison:")
    
    start_time = time.time()
    bubble_sort(arr.copy())
    end_time = time.time()
    print(f"Bubble Sort: {end_time - start_time:.4f} seconds")
    
    start_time = time.time()
    insertion_sort(arr.copy())
    end_time = time.time()
    print(f"Insertion Sort: {end_time - start_time:.4f} seconds")
    
    start_time = time.time()
    selection_sort(arr.copy())
    end_time = time.time()
    print(f"Selection Sort: {end_time - start_time:.4f} seconds")
    
    start_time = time.time()
    quick_sort(arr.copy())
    end_time = time.time()
    print(f"Quick Sort: {end_time - start_time:.4f} seconds")
    
    start_time = time.time()
    merge_sort(arr.copy())
    end_time = time.time()
    print(f"Merge Sort: {end_time - start_time:.4f} seconds")