#!/usr/bin/env python3
import time
import random
import numpy as np

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
        min_index = i
        for j in range(i + 1, n):
            if arr[min_index] > arr[j]:
                min_index = j
        arr[i], arr[min_index] = arr[min_index], arr[i]
    return arr

def insertion_sort(arr):
    n = len(arr)
    for i in range(1, n):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

def generate_random_array(size):
    return np.random.randint(0, 100, size).tolist()

def time_algorithm(algorithm, array):
    start_time = time.time()
    algorithm(array)
    end_time = time.time()
    return end_time - start_time

if __name__ == '__main__':
    for _ in range(5):  # repeat the test 5 times
        size = 1000  # generate an array of this size
        array = generate_random_array(size)
        print(f"Testing with array of {size} elements...")
        algorithms = [bubble_sort, selection_sort, insertion_sort, quick_sort]
        for algorithm in algorithms:
            time_taken = time_algorithm(algorithm, array.copy())  # copy the array to avoid modifying it
            print(f"{algorithm.__name__}: {time_taken:.6f} seconds")