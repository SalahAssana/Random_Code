import numpy as np
import matplotlib.pyplot as plt
import time
from random import randint

def generate_random_array(size):
    return [randint(0, 100) for _ in range(size)]

def bubble_sort(array):
    n = len(array)
    for i in range(n):
        for j in range(0, n-i-1):
            if array[j] > array[j+1]:
                array[j], array[j+1] = array[j+1], array[j]
    return array

def selection_sort(array):
    n = len(array)
    for i in range(n):
        min_index = i
        for j in range(i+1, n):
            if array[j] < array[min_index]:
                min_index = j
        array[i], array[min_index] = array[min_index], array[i]
    return array

def insertion_sort(array):
    n = len(array)
    for i in range(1, n):
        key = array[i]
        j = i-1
        while j >= 0 and array[j] > key:
            array[j+1] = array[j]
            j -= 1
        array[j+1] = key
    return array

def visualize_sorting_algorithms(array_size, repeat_count):
    arrays = [generate_random_array(array_size) for _ in range(repeat_count)]
    
    bubble_times = []
    selection_times = []
    insertion_times = []
    
    for array in arrays:
        start_time = time.time()
        bubble_sort(array.copy())
        end_time = time.time()
        bubble_times.append(end_time - start_time)
        
        start_time = time.time()
        selection_sort(array.copy())
        end_time = time.time()
        selection_times.append(end_time - start_time)
        
        start_time = time.time()
        insertion_sort(array.copy())
        end_time = time.time()
        insertion_times.append(end_time - start_time)

    plt.bar(['Bubble Sort', 'Selection Sort', 'Insertion Sort'], [np.mean(bubble_times), np.mean(selection_times), np.mean(insertion_times)])
    plt.xlabel('Sorting Algorithm')
    plt.ylabel('Average Time (seconds)')
    plt.title('Sorting Algorithms Performance Comparison')
    plt.show()

if __name__ == '__main__':
    visualize_sorting_algorithms(100, 10)