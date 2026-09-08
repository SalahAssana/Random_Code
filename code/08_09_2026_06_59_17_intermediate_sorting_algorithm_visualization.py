import matplotlib.pyplot as plt
import numpy as np
import time

def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
        yield arr.copy()

def quicksort(arr):
    if len(arr) <= 1:
        return [arr]
    pivot = arr[0]
    less = [x for x in arr[1:] if x < pivot]
    equal = [x for x in arr if x == pivot]
    greater = [x for x in arr[1:] if x > pivot]
    results = quicksort(less) + [pivot] * len(equal) + quicksort(greater)
    yield from results

def visualize_sorting_algorithm(algorithm, data):
    fig, ax = plt.subplots()
    ax.set_title('Sorting Algorithm Visualization')
    ax.set_xlabel('Index')
    ax.set_ylabel('Value')
    line, = ax.plot([], [], 'o-')

    def update(i):
        line.set_data(range(len(data)), data)
        yield i

    for frame in algorithm(data):
        data = list(frame)
        yield from update(len(data))

def main():
    if __name__ == '__main__':
        # Example usage: Visualize bubble sort on the array [5, 3, 8, 4, 2]
        data = np.random.randint(1, 100, size=10).tolist()
        print("Original Data:", data)
        
        plt.ion()
        gen = visualize_sorting_algorithm(bubble_sort, data)
        for i in range(20):
            plt.pause(.01)
            plt.clf()
            next(gen)
        plt.ioff()
        plt.show()

if __name__ == '__main__':
    main()