import random
import time
from collections import defaultdict

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
        while j >= 0 and key < arr[j]:
            arr[j+1] = arr[j]
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

def compare_algorithms():
    sizes = [100, 500, 1000, 2000, 5000]
    algorithms = ['bubble', 'selection', 'insertion', 'quick']
    results = defaultdict(dict)
    
    for size in sizes:
        arr = [random.randint(1, 100) for _ in range(size)]
        
        for algorithm in algorithms:
            start_time = time.time()
            if algorithm == 'bubble':
                sorted_arr = bubble_sort(arr.copy())
            elif algorithm == 'selection':
                sorted_arr = selection_sort(arr.copy())
            elif algorithm == 'insertion':
                sorted_arr = insertion_sort(arr.copy())
            else:
                sorted_arr = quick_sort(arr.copy())
            
            end_time = time.time()
            results[size][algorithm] = end_time - start_time
    
    for size, algorithms in results.items():
        print(f"Size: {size}")
        for algorithm, times in algorithms.items():
            print(f"{algorithm}: {times:.4f} seconds")

if __name__ == '__main__':
    compare_algorithms()