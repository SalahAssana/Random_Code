# Sorting Algorithm Comparison
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

def merge_sort(arr: List[int]) -> List[int]:
    n = len(arr)
    if n <= 1:
        return arr
    mid = n // 2
    left_half = merge_sort(arr[:mid])
    right_half = merge_sort(arr[mid:])
    result = []
    while len(left_half) > 0 and len(right_half) > 0:
        if left_half[0] < right_half[0]:
            result.append(left_half.pop(0))
        else:
            result.append(right_half.pop(0))
    result.extend(left_half)
    result.extend(right_half)
    return result

def compare_sorting_algorithms(arr: List[int]) -> None:
    algorithms = [bubble_sort, insertion_sort, merge_sort]
    for algo in algorithms:
        start_time = time.time()
        sorted_arr = algo(arr[:])
        end_time = time.time()
        print(f"Algorithm: {algo.__name__}")
        print(f"Time taken: {end_time - start_time} seconds")
        print("Sorted array:", sorted_arr)
        print()

if __name__ == '__main__':
    arr = [random.randint(0, 100) for _ in range(10)]
    compare_sorting_algorithms(arr)