import tkinter as tk
from random import randint

class SortingAlgorithmVisualizer:
    def __init__(self):
        self.root = tk.Tk()
        self.canvas = tk.Canvas(self.root, width=800, height=400)
        self.canvas.pack()
        self.array_length = 20
        self.array = [randint(0, 100) for _ in range(self.array_length)]
        self.draw_array()

    def draw_array(self):
        self.canvas.delete("all")
        x_width = 800 / len(self.array)
        for i, val in enumerate(self.array):
            self.canvas.create_rectangle(i * x_width, 400 - (val / 100) * 400, (i + 1) * x_width, 400, fill='blue')
        self.root.update()

    def bubble_sort(self):
        n = len(self.array)
        for i in range(n):
            for j in range(0, n-i-1):
                if self.array[j] > self.array[j+1]:
                    self.array[j], self.array[j+1] = self.array[j+1], self.array[j]
                    self.draw_array()
                    self.root.update_idletasks()
        print("Bubble sort done!")

    def quicksort(self, arr):
        if len(arr) <= 1:
            return arr
        pivot = arr[len(arr)//2]
        left = [x for x in arr if x < pivot]
        middle = [x for x in arr if x == pivot]
        right = [x for x in arr if x > pivot]
        self.draw_array()
        self.root.update_idletasks()
        return quicksort(left) + middle + quicksort(right)

    def start_algorithm(self, algorithm):
        if algorithm.lower() == 'bubble sort':
            self.bubble_sort()
        elif algorithm.lower() == 'quicksort':
            sorted_array = self.quicksort(self.array)
            self.array = sorted_array
        else:
            print("Invalid algorithm!")

    def run(self):
        self.root.after(100, self.start_algorithm, 'Bubble Sort')
        self.root.mainloop()

if __name__ == '__main__':
    app = SortingAlgorithmVisualizer()
    app.run()