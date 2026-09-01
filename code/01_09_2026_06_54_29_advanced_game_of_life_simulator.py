import numpy as np
import matplotlib.pyplot as plt
from concurrent.futures import ThreadPoolExecutor
from time import sleep

class GameOfLife:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.grid = np.random.randint(0, 2, (height, width), dtype=int)

    def generate_next_generation(self):
        next_grid = np.zeros((self.height, self.width), dtype=int)
        for i in range(self.height):
            for j in range(self.width):
                live_neighbors = self.count_live_neighbors(i, j)
                if self.grid[i, j] == 1:
                    if (live_neighbors < 2) or (live_neighbors > 3):
                        next_grid[i, j] = 0
                    else:
                        next_grid[i, j] = 1
                else:
                    if live_neighbors == 3:
                        next_grid[i, j] = 1
        self.grid = next_grid

    def count_live_neighbors(self, i, j):
        neighbors = 0
        for x in range(-1, 2):
            for y in range(-1, 2):
                if (x == 0) and (y == 0):
                    continue
                if ((i + x >= self.height) or (i + x < 0)) or ((j + y >= self.width) or (j + y < 0)):
                    continue
                neighbors += self.grid[i + x, j + y]
        return neighbors

    def visualize(self):
        plt.imshow(self.grid, cmap='gray', interpolation='none')
        plt.show()

    def run_simulation(self, generations):
        for _ in range(generations):
            self.generate_next_generation()
            sleep(0.1)  # Pause to observe the simulation
            self.visualize()

if __name__ == '__main__':
    game = GameOfLife(100, 100)
    with ThreadPoolExecutor() as executor:
        executor.submit(game.run_simulation, 10)