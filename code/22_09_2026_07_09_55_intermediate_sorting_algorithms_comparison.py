# Sorting Algorithms Comparison
import random
import time
import matplotlib.pyplot as plt

def generate_random_array(size):
    """Generate an array of random integers"""
    return [random.randint(0, 100) for _ in range(size)]

def bubble_sort(arr):
    """Bubble sort algorithm"""
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr

def selection_sort(arr):
    """Selection sort algorithm"""
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
    return arr

def insertion_sort(arr):
    """Insertion sort algorithm"""
    n = len(arr)
    for i in range(1, n):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

def merge_sort(arr):
    """Merge sort algorithm"""
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]
    return merge(merge_sort(left_half), merge_sort(right_half))

def merge(left, right):
    """Merge function for merge sort"""
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

def main():
    # Generate random arrays of different sizes
    array_sizes = [100, 500, 1000]
    algorithms = [bubble_sort, selection_sort, insertion_sort, merge_sort]

    for size in array_sizes:
        print(f"Testing with array size {size}")
        arr = generate_random_array(size)
        print("Before sorting:")
        print(arr)

        # Time each algorithm
        times = []
        for algo in algorithms:
            start_time = time.time()
            sorted_arr = algo(arr.copy())
            end_time = time.time()
            times.append(end_time - start_time)

            print(f"After sorting with {algo.__name__}:")
            print(sorted_arr)
            print()

        # Plot the execution times
        plt.plot(array_sizes, times, 'o-')
        plt.xlabel('Array size')
        plt.ylabel('Execution time (seconds)')
        plt.title('Sorting Algorithm Comparison')
        plt.show()

if __name__ == '__main__':
    main()