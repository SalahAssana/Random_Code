import random
import time
import matplotlib.pyplot as plt
import numpy as np

# Define some constants
WIDTH = 800
HEIGHT = 600
ARRAY_SIZE = 100
MIN_VALUE = 1
MAX_VALUE = 100

class Visualization:
    def __init__(self):
        self.array = [random.randint(MIN_VALUE, MAX_VALUE) for _ in range(ARRAY_SIZE)]
        self.fig, self.ax = plt.subplots()
        self.bar_rects = self.ax.bar(range(len(self.array)), self.array)
        self.ax.set_ylim([0, 150])
        self.ax.set_xlim([0, ARRAY_SIZE])

    def draw_array(self):
        for rect, height in zip(self.bar_rects, self.array):
            rect.set_height(height)

    def update(self):
        plt.pause(0.01)  # Pause to allow the plot to update
        plt.draw()  # Redraw the canvas

    def sort(self, algorithm):
        if algorithm == "quicksort":
            quicksort(self.array, 0, len(self.array) - 1)
        elif algorithm == "mergesort":
            mergesort(self.array, 0, len(self.array) - 1)
        else:
            print("Invalid algorithm")

    def show(self):
        plt.show(block=True)

def quicksort(arr, low, high):
    if low >= high:
        return
    pivot_index = partition(arr, low, high)
    quicksort(arr, low, pivot_index-1)
    quicksort(arr, pivot_index+1, high)

def partition(arr, low, high):
    pivot = arr[high]
    i = low - 1
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i+1], arr[high] = arr[high], arr[i+1]
    return i + 1

def mergesort(arr, low, high):
    if low >= high:
        return
    mid = (low + high) // 2
    mergesort(arr, low, mid)
    mergesort(arr, mid + 1, high)
    merge(arr, low, mid, high)

def merge(arr, low, mid, high):
    left = arr[low:mid+1]
    right = arr[mid+1:high+1]
    result = []
    while len(left) > 0 and len(right) > 0:
        if left[0] <= right[0]:
            result.append(left.pop(0))
        else:
            result.append(right.pop(0))
    result.extend(left)
    result.extend(right)
    arr[low:high+1] = result

if __name__ == '__main__':
    vis = Visualization()
    while True:
        print("Enter 1 to visualize quicksort, 2 to visualize mergesort, or 3 to exit:")
        choice = input()
        if choice == '1':
            vis.sort("quicksort")
            vis.draw_array()
            vis.update()
            vis.show()
            break
        elif choice == '2':
            vis.sort("mergesort")
            vis.draw_array()
            vis.update()
            vis.show()
            break
        elif choice == '3':
            plt.close('all')
            break
        else:
            print("Invalid choice. Please try again.")