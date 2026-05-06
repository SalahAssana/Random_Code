import random
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

class SortingAlgorithmVisualizer:
    def __init__(self):
        self.array = [random.randint(0, 100) for _ in range(20)]
        self.width = 800
        self.height = 200
        self.bar_width = self.width / len(self.array)
        self.fig, self.ax = plt.subplots()

    def generate_bars(self):
        self.ax.clear()
        bars = self.ax.bar(range(len(self.array)), self.array, self.bar_width)

    def quicksort_visualize(self, arr):
        if len(arr) <= 1:
            return arr

        pivot = arr[0]
        less = [x for x in arr[1:] if x < pivot]
        equal = [x for x in arr if x == pivot]
        greater = [x for x in arr[1:] if x > pivot]

        self.generate_bars()
        plt.draw()
        plt.pause(0.01)

        self.ax.cla()

        self.quicksort_visualize(less)
        self.quicksort_visualize(greater)

    def merge_sort_visualize(self, arr):
        if len(arr) <= 1:
            return arr

        mid = len(arr) // 2
        left_half = arr[:mid]
        right_half = arr[mid:]

        self.generate_bars()
        plt.draw()
        plt.pause(0.01)

        self.ax.cla()

        self.merge_sort_visualize(left_half)
        self.merge_sort_visualize(right_half)

    def visualize(self):
        self.quicksort_visualize(self.array[:])
        self.merge_sort_visualize(self.array[:])

    if __name__ == '__main__':
        visualizer = SortingAlgorithmVisualizer()
        visualizer.visualize()
        plt.show()