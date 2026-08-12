import tkinter as tk
from random import randint

class BubbleSortVisualizer:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Bubble Sort Visualizer")
        self.canvas = tk.Canvas(self.root, width=800, height=600)
        self.canvas.pack()
        self.array = [randint(1, 100) for _ in range(20)]
        self.draw_array()

    def draw_array(self):
        self.canvas.delete('all')
        x_width = 40
        y_height = 30
        for i, val in enumerate(self.array):
            x0 = (i * x_width)
            y0 = 550 - (val // 10) * y_height
            x1 = (i * x_width) + x_width
            y1 = 550
            self.canvas.create_rectangle(x0, y0, x1, y1, fill='blue')
        self.root.after(1000, self.sort_array)

    def draw_swap(self, i, j):
        x0 = (i * 40)
        y0 = 550 - (self.array[i] // 10) * 30
        x1 = (i * 40) + 40
        y1 = 550

        x2 = (j * 40)
        y2 = 550 - (self.array[j] // 10) * 30
        x3 = (j * 40) + 40
        y3 = 550

        self.canvas.create_rectangle(x0, y0, x1, y1, fill='red')
        self.canvas.create_rectangle(x2, y2, x3, y3, fill='red')

    def sort_array(self):
        for i in range(len(self.array)):
            for j in range(len(self.array) - 1):
                if self.array[j] > self.array[j + 1]:
                    self.array[j], self.array[j + 1] = self.array[j + 1], self.array[j]
                    self.draw_array()
                    self.root.update_idletasks()
                    self.root.after(1000)
        self.canvas.delete('all')
        for i, val in enumerate(self.array):
            x0 = (i * 40)
            y0 = 550 - (val // 10) * 30
            x1 = (i * 40) + 40
            y1 = 550
            self.canvas.create_rectangle(x0, y0, x1, y1, fill='blue')
        self.root.mainloop()

    def run(self):
        self.run_sort()

    def run_sort(self):
        if __name__ == '__main__':
            visualizer = BubbleSortVisualizer()
            visualizer.run()

if __name__ == '__main__':
    bubble_sort_visualizer = BubbleSortVisualizer()