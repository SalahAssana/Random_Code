import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d

class GameOfLife:
    def __init__(self, width=50, height=50):
        self.width = width
        self.height = height
        self.grid = np.random.choice([0, 1], size=(height, width), p=[0.5, 0.5])

    def count_neighbors(self, x, y):
        neighbors = [(x-1, y-1), (x-1, y), (x-1, y+1), (x, y-1), (x, y+1), (x+1, y-1), (x+1, y), (x+1, y+1)]
        count = 0
        for nx, ny in neighbors:
            if nx >= 0 and ny >= 0 and nx < self.height and ny < self.width:
                count += self.grid[ny, ny]
        return count

    def next_generation(self):
        new_grid = np.zeros((self.height, self.width))
        for y in range(self.height):
            for x in range(self.width):
                live_neighbors = self.count_neighbors(x, y)
                if self.grid[y, x] == 1:
                    if live_neighbors < 2 or live_neighbors > 3:
                        new_grid[y, x] = 0
                    else:
                        new_grid[y, x] = 1
                elif live_neighbors == 3:
                    new_grid[y, x] = 1
        self.grid = new_grid

    def visualize(self):
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        ax.scatter(np.arange(self.width), np.arange(self.height), self.grid.flatten(), c=self.grid.flatten())
        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.set_zlabel('Cell state (0 or 1)')
        plt.show()

    def run(self, generations):
        for _ in range(generations):
            self.next_generation()
            if _ % 10 == 0:
                self.visualize()

if __name__ == '__main__':
    game = GameOfLife()
    game.run(100)