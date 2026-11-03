import random
import matplotlib.pyplot as plt
import time

class SortingAlgorithmVisualizer:
    def __init__(self):
        self.algorithms = {
            'Bubble Sort': self.bubble_sort,
            'Selection Sort': self.selection_sort,
            'Insertion Sort': self.insertion_sort,
            'Merge Sort': self.merge_sort,
            'Quick Sort': self.quick_sort
        }
        self.data_sizes = [100, 500, 1000]
        self.algorithms_to_plot = ['Bubble Sort', 'Selection Sort', 'Insertion Sort']

    def generate_random_data(self, size):
        return [random.randint(1, 100) for _ in range(size)]

    def bubble_sort(self, arr):
        n = len(arr)
        for i in range(n):
            for j in range(0, n - i - 1):
                if arr[j] > arr[j + 1]:
                    arr[j], arr[j + 1] = arr[j + 1], arr[j]
        return arr

    def selection_sort(self, arr):
        n = len(arr)
        for i in range(n):
            min_idx = i
            for j in range(i + 1, n):
                if arr[j] < arr[min_idx]:
                    min_idx = j
            arr[i], arr[min_idx] = arr[min_idx], arr[i]
        return arr

    def insertion_sort(self, arr):
        n = len(arr)
        for i in range(1, n):
            key = arr[i]
            j = i - 1
            while j >= 0 and arr[j] > key:
                arr[j + 1] = arr[j]
                j -= 1
            arr[j + 1] = key
        return arr

    def merge_sort(self, arr):
        if len(arr) <= 1:
            return arr
        mid = len(arr) // 2
        left_half = self.merge_sort(arr[:mid])
        right_half = self.merge_sort(arr[mid:])
        return self.merge(left_half, right_half)

    def merge(self, left, right):
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

    def quick_sort(self, arr):
        if len(arr) <= 1:
            return arr
        pivot = arr[0]
        less_than_pivot = [x for x in arr[1:] if x < pivot]
        equal_to_pivot = [x for x in arr if x == pivot]
        greater_than_pivot = [x for x in arr[1:] if x > pivot]
        return self.quick_sort(less_than_pivot) + equal_to_pivot + self.quick_sort(greater_than_pivot)

    def visualize(self):
        plt.figure(figsize=(10, 6))
        for algorithm in self.algorithms_to_plot:
            times = []
            for size in self.data_sizes:
                arr = self.generate_random_data(size)
                start_time = time.time()
                self.algorithms[algorithm](arr)
                end_time = time.time()
                times.append(end_time - start_time)
            plt.plot(self.data_sizes, times, label=algorithm)
        plt.xlabel('Data Size')
        plt.ylabel('Time (seconds)')
        plt.title('Sorting Algorithm Performance')
        plt.legend()
        plt.show()

if __name__ == '__main__':
    visualizer = SortingAlgorithmVisualizer()
    visualizer.visualize()