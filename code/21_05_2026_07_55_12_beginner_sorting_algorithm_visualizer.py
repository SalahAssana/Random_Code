import tkinter as tk
from random import randint

class SortingAlgorithmVisualizer:
    def __init__(self, root):
        self.root = root
        self.canvas = tk.Canvas(self.root, width=800, height=600)
        self.canvas.pack()
        self.array = [randint(0, 100) for _ in range(20)]
        self.sorted_array = sorted(self.array)
        self.draw_array()

    def draw_array(self):
        self.canvas.delete("all")
        for i, val in enumerate(self.array):
            x1 = (i / len(self.array)) * 800
            y1 = 600 - (val / max(self.array) * 500)
            x2 = ((i+1) / len(self.array)) * 800
            y2 = 600 - ((self.sorted_array[i] / max(self.sorted_array)) * 500)
            self.canvas.create_line(x1, y1, x2, y2)

    def quicksort(self):
        if len(self.array) <= 1:
            return
        pivot = self.array[0]
        left = [x for x in self.array[1:] if x < pivot]
        middle = [x for x in self.array[1:] if x == pivot]
        right = [x for x in self.array[1:] if x > pivot]
        self.array = left + middle + right
        self.draw_array()
        self.root.after(100, self.quicksort)

    def run(self):
        self.quicksort()

if __name__ == '__main__':
    root = tk.Tk()
    app = SortingAlgorithmVisualizer(root)
    app.run()
    root.mainloop()