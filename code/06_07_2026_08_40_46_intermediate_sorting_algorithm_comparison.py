#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import random
import time
from typing import List

def bubble_sort(arr: List[int]) -> None:
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]

def selection_sort(arr: List[int]) -> None:
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]

def insertion_sort(arr: List[int]) -> None:
    n = len(arr)
    for i in range(1, n):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

def test_sorting_algorithm(algorithm: str, size: int) -> None:
    if algorithm == "bubble":
        sort_function = bubble_sort
    elif algorithm == "selection":
        sort_function = selection_sort
    elif algorithm == "insertion":
        sort_function = insertion_sort
    else:
        print(f"Invalid algorithm '{algorithm}'")
        return

    arr = [random.randint(0, 100) for _ in range(size)]
    start_time = time.time()
    sort_function(arr)
    end_time = time.time()

    print(f"{algorithm} sorting {size} elements took {end_time - start_time:.2f} seconds")

if __name__ == '__main__':
    algorithms = ["bubble", "selection", "insertion"]
    sizes = [100, 500, 1000]
    
    for algorithm in algorithms:
        for size in sizes:
            test_sorting_algorithm(algorithm, size)