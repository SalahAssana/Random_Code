import matplotlib.pyplot as plt
import numpy as np
import random

class SortingAlgorithmVisualizer:
    def __init__(self):
        self.algorithms = {
            'Bubble Sort': self.bubble_sort,
            'Selection Sort': self.selection_sort,
            'Insertion Sort': self.insertion_sort,
            'Merge Sort': self.merge_sort,
            'Quick Sort': self.quick_sort
        }

    def generate_random_array(self, size):
        return [random.randint(0, 100) for _ in range(size)]

    def draw_array(self, array):
        plt.bar(range(len(array)), array)
        plt.xlabel('Index')
        plt.ylabel('Value')
        plt.title('Array Visualization')
        plt.show()

    def bubble_sort(self, array):
        n = len(array)
        for i in range(n):
            for j in range(0, n - i - 1):
                if array[j] > array[j + 1]:
                    array[j], array[j + 1] = array[j + 1], array[j]
        return array

    def selection_sort(self, array):
        n = len(array)
        for i in range(n):
            min_idx = i
            for j in range(i + 1, n):
                if array[j] < array[min_idx]:
                    min_idx = j
            array[i], array[min_idx] = array[min_idx], array[i]
        return array

    def insertion_sort(self, array):
        for i in range(1, len(array)):
            key = array[i]
            j = i - 1
            while j >= 0 and array[j] > key:
                array[j + 1] = array[j]
                j -= 1
            array[j + 1] = key
        return array

    def merge_sort(self, array):
        if len(array) <= 1:
            return array
        mid = len(array) // 2
        left_half = self.merge_sort(array[:mid])
        right_half = self.merge_sort(array[mid:])
        return self.merge(left_half, right_half)

    def merge(self, left, right):
        result = []
        i, j = 0, 0
        while i < len(left) and j < len(right):
            if left[i] <= right[j]:
                result.append(left[i])
                i += 1
            else:
                result.append(right[j])
                j += 1
        result.extend(left[i:])
        result.extend(right[j:])
        return result

    def quick_sort(self, array):
        if len(array) <= 1:
            return array
        pivot = array[len(array) // 2]
        left = [x for x in array if x < pivot]
        middle = [x for x in array if x == pivot]
        right = [x for x in array if x > pivot]
        return self.quick_sort(left) + middle + self.quick_sort(right)

    def visualize(self, algorithm_name):
        array = self.generate_random_array(20)
        print(f'Visualizing {algorithm_name}...')
        plt.ion()
        plt.show(block=False)
        for _ in range(10):
            self.draw_array(array[:])
            if algorithm_name == 'Bubble Sort':
                array = self.bubble_sort(array[:])
            elif algorithm_name == 'Selection Sort':
                array = self.selection_sort(array[:])
            elif algorithm_name == 'Insertion Sort':
                array = self.insertion_sort(array[:])
            elif algorithm_name == 'Merge Sort':
                array = self.merge_sort(array[:])
            elif algorithm_name == 'Quick Sort':
                array = self.quick_sort(array[:])
            plt.pause(0.1)
        plt.close()

    def main(self):
        if __name__ == '__main__':
            visualizer = SortingAlgorithmVisualizer()
            for algorithm in self.algorithms:
                print(f'Visualizing {algorithm}...')
                self.visualize(algorithm)
                input('Press Enter to continue...')

if __name__ == '__main__':
    SortingAlgorithmVisualizer().main()