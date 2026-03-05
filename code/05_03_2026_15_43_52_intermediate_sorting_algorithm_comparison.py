#!/usr/bin/env python3
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

def quick_sort(arr: List[int]) -> List[int]:
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

def generate_random_array(size: int, max_value: int) -> List[int]:
    return [random.randint(0, max_value) for _ in range(size)]

def compare_algorithms():
    sizes = [100, 500, 1000]
    max_values = [100, 500, 1000]
    
    print("Sorting Algorithm Comparison")
    print("---------------------------")
    
    for size in sizes:
        for max_value in max_values:
            arr = generate_random_array(size, max_value)
            
            start_time = time.time()
            bubble_sort(arr.copy())
            end_time = time.time()
            bubble_time = end_time - start_time
            
            start_time = time.time()
            quick_sort(arr.copy())
            end_time = time.time()
            quick_time = end_time - start_time
            
            print(f"Array size: {size}, Max value: {max_value}")
            print(f"Bubble sort time: {bubble_time:.4f} seconds")
            print(f"Quick sort time: {quick_time:.4f} seconds")
            print()

if __name__ == '__main__':
    compare_algorithms()