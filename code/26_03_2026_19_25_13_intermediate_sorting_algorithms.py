def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr

def selection_sort(arr):
    n = len(arr)
    for i in range(n):
        min_index = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_index]:
                min_index = j
        arr[i], arr[min_index] = arr[min_index], arr[i]
    return arr

def insertion_sort(arr):
    n = len(arr)
    for i in range(1, n):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

import random
import time
import matplotlib.pyplot as plt

if __name__ == '__main__':
    # Generate synthetic data
    sizes = [100, 500, 1000, 2000, 5000]
    times_bubble = []
    times_selection = []
    times_insertion = []

    for size in sizes:
        arr = [random.randint(1, 100) for _ in range(size)]

        # Bubble sort
        start_time = time.time()
        bubble_sort(arr.copy())
        end_time = time.time()
        times_bubble.append(end_time - start_time)

        # Selection sort
        start_time = time.time()
        selection_sort(arr.copy())
        end_time = time.time()
        times_selection.append(end_time - start_time)

        # Insertion sort
        start_time = time.time()
        insertion_sort(arr.copy())
        end_time = time.time()
        times_insertion.append(end_time - start_time)

    plt.plot(sizes, times_bubble, 'r', label='Bubble Sort')
    plt.plot(sizes, times_selection, 'g', label='Selection Sort')
    plt.plot(sizes, times_insertion, 'b', label='Insertion Sort')
    plt.xlabel('Array size')
    plt.ylabel('Time (seconds)')
    plt.title('Sorting Algorithm Performance Comparison')
    plt.legend()
    plt.show()