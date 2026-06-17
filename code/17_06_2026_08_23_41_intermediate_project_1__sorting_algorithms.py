import time
import random
import sys

def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr

def selection_sort(arr):
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i+1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
    return arr

def insertion_sort(arr):
    n = len(arr)
    for i in range(1, n):
        key = arr[i]
        j = i-1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j+1] = key
    return arr

def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr)//2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

def generate_random_array(size, min_value, max_value):
    return [random.randint(min_value, max_value) for _ in range(size)]

if __name__ == '__main__':
    size = 10000
    min_value = 0
    max_value = 100

    print("Generating random array of size", size)
    arr = generate_random_array(size, min_value, max_value)

    print("\nSorting algorithms and their execution times:")
    for algo in [bubble_sort, selection_sort, insertion_sort, quick_sort]:
        start_time = time.time()
        result = algo(arr.copy())
        end_time = time.time()
        execution_time = end_time - start_time
        print(f"{algo.__name__}: {execution_time:.6f} seconds")