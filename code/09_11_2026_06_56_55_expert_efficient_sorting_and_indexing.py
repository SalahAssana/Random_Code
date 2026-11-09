#!/usr/bin/env python3
from typing import List, Tuple
import random
import time
import heapq

def insertion_sort(arr: List[int]) -> List[int]:
    """Insertion sort algorithm"""
    sorted_arr = []
    for num in arr:
        pos = len(sorted_arr)
        while pos and (num < int(sorted_arr[pos-1])):
            sorted_arr.insert(pos - 1, num)
            pos -= 1
        else:
            sorted_arr.append(num)
    return sorted_arr

def merge_sort(arr: List[int]) -> List[int]:
    """Merge sort algorithm"""
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left_half = merge_sort(arr[:mid])
    right_half = merge_sort(arr[mid:])
    return list(heapq.merge(left_half, right_half))

def binary_search(arr: List[int], target: int) -> Tuple[bool, int]:
    """Binary search algorithm"""
    low, high = 0, len(arr)
    while low < high:
        mid = (low + high) // 2
        if arr[mid] == target:
            return True, mid
        elif arr[mid] < target:
            low = mid + 1
        else:
            high = mid
    return False, -1

def create_indexed_dataset(arr: List[int], index_size: int) -> Tuple[List[int], List[Tuple[int, int]]]:
    """Create an indexed dataset"""
    sorted_arr = merge_sort(arr)
    indexed_dataset = [(num, i) for i, num in enumerate(sorted_arr)]
    return sorted_arr, indexed_dataset

def query_indexed_dataset(sorted_arr: List[int], indexed_dataset: List[Tuple[int, int]], target: int) -> Tuple[bool, int]:
    """Query an indexed dataset"""
    low, high = 0, len(indexed_dataset)
    while low < high:
        mid = (low + high) // 2
        if indexed_dataset[mid][0] == target:
            return True, indexed_dataset[mid][1]
        elif indexed_dataset[mid][0] < target:
            low = mid + 1
        else:
            high = mid
    return False, -1

def main():
    """Main function"""
    # Synthetic data generation
    num_elements = 100000
    random_data = [random.randint(0, 100) for _ in range(num_elements)]
    
    start_time = time.time()
    sorted_arr = insertion_sort(random_data)
    end_time = time.time()
    print(f"Insertion sort took {end_time - start_time} seconds")
    
    indexed_dataset = create_indexed_dataset(sorted_arr, index_size=1000)
    
    query_target = 50
    result = query_indexed_dataset(*indexed_dataset, target=query_target)
    if result[0]:
        print(f"Found {query_target} at index {result[1]} in the indexed dataset")
    else:
        print(f"{query_target} not found in the indexed dataset")

if __name__ == '__main__':
    main()