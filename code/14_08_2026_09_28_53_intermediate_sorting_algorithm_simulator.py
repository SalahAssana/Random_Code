import random
import time
import matplotlib.pyplot as plt

def generate_random_array(size):
    return [random.randint(0, 100) for _ in range(size)]

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
        min_idx = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
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

def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]
    return merge(merge_sort(left_half), merge_sort(right_half))

def merge(left, right):
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

def visualize_sorting_algorithms():
    sizes = [100, 500, 1000]
    algorithms = ['Bubble Sort', 'Selection Sort', 'Insertion Sort']
    for size in sizes:
        arr = generate_random_array(size)
        for algorithm in algorithms:
            if algorithm == 'Bubble Sort':
                start_time = time.time()
                sorted_arr = bubble_sort(arr.copy())
                end_time = time.time()
                print(f"Sorting {size} elements using {algorithm}: {end_time - start_time} seconds")
            elif algorithm == 'Selection Sort':
                start_time = time.time()
                sorted_arr = selection_sort(arr.copy())
                end_time = time.time()
                print(f"Sorting {size} elements using {algorithm}: {end_time - start_time} seconds")
            elif algorithm == 'Insertion Sort':
                start_time = time.time()
                sorted_arr = insertion_sort(arr.copy())
                end_time = time.time()
                print(f"Sorting {size} elements using {algorithm}: {end_time - start_time} seconds")

    plt.plot(sizes, [time.time() for _ in range(9)], label='Bubble Sort')
    plt.plot(sizes, [time.time() + 1 for _ in range(3)] + [time.time() + 2 for _ in range(3)] + [time.time() + 3 for _ in range(3)], label='Selection Sort')
    plt.plot(sizes, [time.time() + 4 for _ in range(9)], label='Insertion Sort')
    plt.xlabel('Array Size')
    plt.ylabel('Time (seconds)')
    plt.title('Sorting Algorithms Performance Comparison')
    plt.legend()
    plt.show()

if __name__ == '__main__':
    visualize_sorting_algorithms()