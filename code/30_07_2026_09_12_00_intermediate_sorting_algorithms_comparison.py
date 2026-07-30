def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr

def quicksort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quicksort(left) + middle + quicksort(right)

import random
import time

def generate_random_array(size, max_value):
    return [random.randint(0, max_value) for _ in range(size)]

if __name__ == '__main__':
    sizes = [100, 500, 1000]
    max_values = [10, 50, 100]

    for size in sizes:
        for max_value in max_values:
            array = generate_random_array(size, max_value)
            print(f"Testing with array of size {size} and max value {max_value}:")
            start_time = time.time()
            bubble_sort(array.copy())
            bubble_time = time.time() - start_time
            start_time = time.time()
            quicksort(array.copy())
            quick_time = time.time() - start_time
            print(f"Bubble sort took {bubble_time:.2f} seconds")
            print(f"Quicksort took {quick_time:.2f} seconds\n")