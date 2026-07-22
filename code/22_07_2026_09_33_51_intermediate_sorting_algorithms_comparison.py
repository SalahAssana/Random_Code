#!/usr/bin/env python3
import random
import time
import numpy as np

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
        min_index = i
        for j in range(i + 1, len(arr)):
            if arr[j] < arr[min_index]:
                min_index = j
        arr[i], arr[min_index] = arr[min_index], arr[i]
    return arr

def merge_sort(arr):
    if len(arr) <= 1:
        return arr

    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]

    left_half = merge_sort(left_half)
    right_half = merge_sort(right_half)

    merged = []
    while len(left_half) > 0 and len(right_half) > 0:
        if left_half[0] <= right_half[0]:
            merged.append(left_half.pop(0))
        else:
            merged.append(right_half.pop(0))

    merged.extend(left_half)
    merged.extend(right_half)

    return merged

def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

def main():
    size = 10000
    np.random.seed(0)
    data = np.random.randint(1, 1000000, size).tolist()

    print("Bubblesort:")
    start_time = time.time()
    bubble_sort(data.copy())
    end_time = time.time()
    print(f"Time taken: {end_time - start_time} seconds")

    print("\nInsertionsort:")
    start_time = time.time()
    insertion_sort(data.copy())
    end_time = time.time()
    print(f"Time taken: {end_time - start_time} seconds")

    print("\nSelectionsort:")
    start_time = time.time()
    selection_sort(data.copy())
    end_time = time.time()
    print(f"Time taken: {end_time - start_time} seconds")

    print("\nMergesort:")
    start_time = time.time()
    merge_sort(data.copy())
    end_time = time.time()
    print(f"Time taken: {end_time - start_time} seconds")

    print("\nQuicksort:")
    start_time = time.time()
    quick_sort(data.copy())
    end_time = time.time()
    print(f"Time taken: {end_time - start_time} seconds")

if __name__ == '__main__':
    main()