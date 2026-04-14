import time
import random
import numpy as np

def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
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
            arr[j+1] = arr[j]
            j -= 1
        arr[j+1] = key
    return arr

def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr)//2
    left_half = arr[:mid]
    right_half = arr[mid:]
    left_half = merge_sort(left_half)
    right_half = merge_sort(right_half)
    return list(merge(left_half, right_half))

def merge(left, right):
    merged = []
    left_index = 0
    right_index = 0
    while left_index < len(left) and right_index < len(right):
        if left[left_index] <= right[right_index]:
            merged.append(left[left_index])
            left_index += 1
        else:
            merged.append(right[right_index])
            right_index += 1
    merged.extend(left[left_index:])
    merged.extend(right[right_index:])
    return merged

def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr)//2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

def test_sorting_algorithms():
    n = 1000
    arr = np.random.randint(0, 10000, size=n).tolist()
    
    start_time = time.time()
    bubble_sorted_arr = bubble_sort(arr.copy())
    end_time = time.time()
    print(f"Time taken by Bubble Sort: {end_time - start_time} seconds")
    print(f"Bubble Sorted Array: {bubble_sorted_arr}")

    start_time = time.time()
    selection_sorted_arr = selection_sort(arr.copy())
    end_time = time.time()
    print(f"Time taken by Selection Sort: {end_time - start_time} seconds")
    print(f"Selection Sorted Array: {selection_sorted_arr}")

    start_time = time.time()
    insertion_sorted_arr = insertion_sort(arr.copy())
    end_time = time.time()
    print(f"Time taken by Insertion Sort: {end_time - start_time} seconds")
    print(f"Insertion Sorted Array: {insertion_sorted_arr}")

    start_time = time.time()
    merge_sorted_arr = list(merge_sort(arr.copy()))
    end_time = time.time()
    print(f"Time taken by Merge Sort: {end_time - start_time} seconds")
    print(f"Merge Sorted Array: {merge_sorted_arr}")

    start_time = time.time()
    quick_sorted_arr = quick_sort(arr.copy())
    end_time = time.time()
    print(f"Time taken by Quick Sort: {end_time - start_time} seconds")
    print(f"Quick Sorted Array: {quick_sorted_arr}")

if __name__ == '__main__':