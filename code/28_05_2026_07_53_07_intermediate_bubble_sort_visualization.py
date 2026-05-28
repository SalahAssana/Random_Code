import turtle
import random
import time

class BubbleSortVisualization:
    def __init__(self):
        self.window = turtle.Screen()
        self.window.setup(800, 600)
        self.turtle = turtle.Turtle()
        self.array = [random.randint(1, 100) for _ in range(20)]
        self.delay = 0.5

    def draw_array(self):
        self.turtle.clear()
        self.turtle.penup()
        self.turtle.goto(-200, -250)
        self.turtle.pendown()
        for i, num in enumerate(self.array):
            self.turtle.write(str(num), align="left", font=("Arial", 12, "normal"))
            self.turtle.forward(30)

    def bubble_sort(self):
        n = len(self.array)
        for i in range(n-1):
            swapped = False
            for j in range(0, n-i-1):
                if self.array[j] > self.array[j+1]:
                    self.array[j], self.array[j+1] = self.array[j+1], self.array[j]
                    swapped = True
            if not swapped:
                break
            time.sleep(self.delay)
            self.draw_array()

    def run(self):
        self.draw_array()
        self.bubble_sort()

if __name__ == '__main__':
    visualization = BubbleSortVisualization()
    visualization.run()