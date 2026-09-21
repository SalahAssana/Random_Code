import numpy as np
import matplotlib.pyplot as plt
import time

class GameOfLife:
    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
        self.grid = np.random.randint(0, 2, size=(rows, cols))

    def count_neighbors(self, i, j):
        neighbors = 0
        for x in range(max(0, i-1), min(self.rows, i+2)):
            for y in range(max(0, j-1), min(self.cols, j+2)):
                if (x, y) != (i, j) and self.grid[x, y] == 1:
                    neighbors += 1
        return neighbors

    def next_generation(self):
        new_grid = np.zeros_like(self.grid)
        for i in range(self.rows):
            for j in range(self.cols):
                live_neighbors = self.count_neighbors(i, j)
                if self.grid[i, j] == 1:
                    if live_neighbors in [2, 3]:
                        new_grid[i, j] = 1
                else:
                    if live_neighbors == 3:
                        new_grid[i, j] = 1
        self.grid = new_grid

    def visualize(self):
        plt.imshow(self.grid, cmap='gray', interpolation='nearest')
        plt.show()

def main():
    game = GameOfLife(100, 100)
    for _ in range(100):
        game.next_generation()
        time.sleep(0.1)
        game.visualize()

if __name__ == '__main__':
    main()