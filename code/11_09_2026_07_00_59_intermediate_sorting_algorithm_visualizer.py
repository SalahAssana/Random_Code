import random
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np

# Constants
WIDTH, HEIGHT = 800, 600
BAR_WIDTH, BAR_HEIGHT = 5, 20
ALGO_NAMES = ['Bubble Sort', 'Insertion Sort', 'Selection Sort']
COLORS = [(1, 0, 0), (0, 0, 1), (0.5, 0.5, 0.5)]

class SortingVisualizer:
    def __init__(self):
        self.fig, self.ax = plt.subplots()
        self.ax.set_xlim(0, WIDTH)
        self.ax.set_ylim(0, HEIGHT)
        self.bars = np.random.randint(1, 100, size=50)

    def visualize(self, algo_name):
        if algo_name == 'Bubble Sort':
            self.bubble_sort()
        elif algo_name == 'Insertion Sort':
            self.insertion_sort()
        elif algo_name == 'Selection Sort':
            self.selection_sort()

        plt.show()

    def bubble_sort(self):
        for i in range(len(self.bars)):
            for j in range(len(self.bars) - 1):
                if self.bars[j] > self.bars[j + 1]:
                    self.bars[j], self.bars[j + 1] = self.bars[j + 1], self.bars[j]
                    self.update_bars()

    def insertion_sort(self):
        for i in range(1, len(self.bars)):
            key = self.bars[i]
            j = i - 1
            while j >= 0 and self.bars[j] > key:
                self.bars[j + 1], self.bars[j] = self.bars[j], self.bars[j + 1]
                j -= 1
            self.update_bars()

    def selection_sort(self):
        for i in range(len(self.bars)):
            min_idx = i
            for j in range(i + 1, len(self.bars)):
                if self.bars[j] < self.bars[min_idx]:
                    min_idx = j
            self.bars[i], self.bars[min_idx] = self.bars[min_idx], self.bars[i]
            self.update_bars()

    def update_bars(self):
        self.ax.clear()
        self.ax.bar(range(len(self.bars)), self.bars, width=BAR_WIDTH, height=BAR_HEIGHT)
        plt.draw()

if __name__ == '__main__':
    visualizer = SortingVisualizer()
    for algo_name in ALGO_NAMES:
        print(f"Sorting {algo_name}...")
        visualizer.visualize(algo_name)