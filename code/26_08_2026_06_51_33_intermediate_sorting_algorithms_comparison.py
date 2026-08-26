# Sorting Algorithms Comparison

import random
import time

def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr

def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

def selection_sort(arr):
    for i in range(len(arr)):
        min_idx = i
        for j in range(i + 1, len(arr)):
            if arr[min_idx] > arr[j]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
    return arr

def generate_random_array(size):
    return [random.randint(0, 100) for _ in range(size)]

if __name__ == '__main__':
    size = 5000
    arrays = [generate_random_array(size)]
    
    print("Bubble Sort:")
    start_time = time.time()
    sorted_arrays = [bubble_sort(arr) for arr in arrays]
    end_time = time.time()
    print(f"Time taken: {end_time - start_time} seconds")
    
    print("\nInsertion Sort:")
    start_time = time.time()
    sorted_arrays = [insertion_sort(arr) for arr in arrays]
    end_time = time.time()
    print(f"Time taken: {end_time - start_time} seconds")
    
    print("\nSelection Sort:")
    start_time = time.time()
    sorted_arrays = [selection_sort(arr) for arr in arrays]
    end_time = time.time()
    print(f"Time taken: {end_time - start_time} seconds")