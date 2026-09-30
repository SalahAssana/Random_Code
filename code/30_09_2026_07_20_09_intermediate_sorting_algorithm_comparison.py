def quicksort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quicksort(left) + middle + quicksort(right)

def mergesort(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]
    return merge(mergesort(left_half), mergesort(right_half))

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

def bubblesort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr

def heapify(arr, n, i):
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2
    if l < n and arr[i] < arr[l]:
        largest = l
    if r < n and arr[largest] < arr[r]:
        largest = r
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)

def heap_sort(arr):
    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]
        heapify(arr, i, 0)
    return arr

import random
import time

if __name__ == '__main__':
    # Generate a random array of integers for testing
    arr = [random.randint(0, 100) for _ in range(10)]
    print("Original array:", arr)

    start_time = time.time()
    sorted_arr = quicksort(arr.copy())
    print("Quicksort time: ", time.time() - start_time)
    print("Quicksort result:", sorted_arr)

    start_time = time.time()
    sorted_arr = mergesort(arr.copy())
    print("Mergesort time: ", time.time() - start_time)
    print("Mergesort result:", sorted_arr)

    start_time = time.time()
    sorted_arr = bubblesort(arr.copy())
    print("Bubblesort time: ", time.time() - start_time)
    print("Bubblesort result:", sorted_arr)

    start_time = time.time()
    sorted_arr = heap_sort(arr.copy())
    print("Heapsort time: ", time.time() - start_time)
    print("Heapsort result:", sorted_arr)