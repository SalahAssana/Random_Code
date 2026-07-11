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

def quicksort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quicksort(left) + middle + quicksort(right)

def generate_random_array(size):
    return [random.randint(0, 100) for _ in range(size)]

if __name__ == '__main__':
    sizes = [10, 50, 100, 500, 1000]
    algorithms = ['bubble_sort', 'quicksort']

    for size in sizes:
        arr = generate_random_array(size)
        
        for algo in algorithms:
            start_time = time.time()
            if algo == 'bubble_sort':
                sorted_arr = bubble_sort(arr.copy())
            elif algo == 'quicksort':
                sorted_arr = quicksort(arr.copy())
            
            end_time = time.time()
            elapsed_time = end_time - start_time
            print(f'Array size: {size}, Algorithm: {algo}, Elapsed time: {elapsed_time:.5f} seconds')