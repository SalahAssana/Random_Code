import numpy as np
import matplotlib.pyplot as plt
import random

class GameOfLife:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.grid = np.zeros((width, height), dtype=int)

    def initialize_grid(self):
        for i in range(self.width):
            for j in range(self.height):
                self.grid[i][j] = random.randint(0, 1)

    def print_grid(self):
        plt.imshow(self.grid, cmap='gray', interpolation='nearest')
        plt.show()

    def next_generation(self):
        new_grid = np.zeros((self.width, self.height), dtype=int)
        for i in range(self.width):
            for j in range(self.height):
                count = self.count_neighbors(i, j)
                if self.grid[i][j] == 1 and (count < 2 or count > 3):
                    new_grid[i][j] = 0
                elif self.grid[i][j] == 0 and count == 3:
                    new_grid[i][j] = 1
                else:
                    new_grid[i][j] = self.grid[i][j]
        self.grid = new_grid

    def count_neighbors(self, i, j):
        count = 0
        for x in range(max(0, i-1), min(self.width, i+2)):
            for y in range(max(0, j-1), min(self.height, j+2)):
                if (x != i or y != j) and self.grid[x][y] == 1:
                    count += 1
        return count

    def run_simulation(self, generations):
        self.initialize_grid()
        for _ in range(generations):
            self.print_grid()
            self.next_generation()

if __name__ == '__main__':
    game = GameOfLife(50, 50)
    game.run_simulation(10)