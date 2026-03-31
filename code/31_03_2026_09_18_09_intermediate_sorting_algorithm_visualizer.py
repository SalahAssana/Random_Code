import random
import matplotlib.pyplot as plt
import time

def bubble_sort(arr):
    n = len(arr)
    for i in range(n-1):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr

def plot_array(arr):
    plt.bar(range(len(arr)), arr)
    plt.xlabel('Index')
    plt.ylabel('Value')
    plt.title('Sorting Algorithm Visualization')
    plt.show()

def visualize_sorting_algorithm(arr, algorithm):
    original_arr = arr.copy()
    start_time = time.time()
    sorted_arr = algorithm(arr)
    end_time = time.time()
    print(f"Sorted array: {sorted_arr}")
    print(f"Time taken to sort: {end_time - start_time} seconds")
    
    plt.figure(figsize=(10, 5))
    plt.subplot(2, 1, 1)
    plot_array(original_arr)
    plt.title('Original Array')
    
    plt.subplot(2, 1, 2)
    plot_array(sorted_arr)
    plt.title(f'Sorted Array (Algorithm: {algorithm.__name__})')
    
    plt.tight_layout()
    plt.show()

if __name__ == '__main__':
    arr = [random.randint(0, 100) for _ in range(20)]
    visualize_sorting_algorithm(arr, bubble_sort)