#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import random
import time
from typing import List, Tuple

def insertion_sort(arr: List[int]) -> List[int]:
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

def merge_sort(arr: List[int]) -> List[int]:
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]
    return merge(merge_sort(left_half), merge_sort(right_half))

def merge(left: List[int], right: List[int]) -> List[int]:
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

def quick_sort(arr: List[int]) -> List[int]:
    if len(arr) <= 1:
        return arr
    pivot = arr[0]
    less = [x for x in arr[1:] if x <= pivot]
    greater = [x for x in arr[1:] if x > pivot]
    return quick_sort(less) + [pivot] + quick_sort(greater)

def random_list(length: int, max_value: int) -> List[int]:
    return [random.randint(0, max_value) for _ in range(length)]

if __name__ == '__main__':
    length = 10000
    max_value = 100000
    lists = [
        random_list(length, max_value),
        random_list(length, max_value),
        random_list(length, max_value)
    ]
    
    print("Insertion Sort:")
    start_time = time.time()
    for lst in lists:
        sorted_lst = insertion_sort(lst.copy())
        end_time = time.time()
        print(f"Time taken: {end_time - start_time}")
        print(sorted_lst[:10])
        print()

    print("Merge Sort:")
    start_time = time.time()
    for lst in lists:
        sorted_lst = merge_sort(lst.copy())
        end_time = time.time()
        print(f"Time taken: {end_time - start_time}")
        print(sorted_lst[:10])
        print()

    print("Quick Sort:")
    start_time = time.time()
    for lst in lists:
        sorted_lst = quick_sort(lst.copy())
        end_time = time.time()
        print(f"Time taken: {end_time - start_time}")
        print(sorted_lst[:10])
        print()