import random
import time
from typing import List

def generate_random_list(size: int) -> List[int]:
    """Generate a list of random integers."""
    return [random.randint(0, 1000) for _ in range(size)]

def bubble_sort(arr: List[int]) -> None:
    """Bubble sort algorithm implementation."""
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

def selection_sort(arr: List[int]) -> None:
    """Selection sort algorithm implementation."""
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]

def insertion_sort(arr: List[int]) -> None:
    """Insertion sort algorithm implementation."""
    n = len(arr)
    for i in range(1, n):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

def measure_algorithm_time(func: callable, arr: List[int]) -> float:
    """Measure the time taken by an algorithm."""
    start_time = time.time()
    func(arr)
    end_time = time.time()
    return end_time - start_time

if __name__ == '__main__':
    sizes = [1000, 5000, 10000]
    algorithms = [bubble_sort, selection_sort, insertion_sort]

    for size in sizes:
        random_arr = generate_random_list(size)
        print(f"Size: {size}")

        for algorithm in algorithms:
            print(f"{algorithm.__name__}:")
            start_time = time.time()
            algorithm(random_arr.copy())
            end_time = time.time()
            print(f"Time taken: {end_time - start_time} seconds\n")