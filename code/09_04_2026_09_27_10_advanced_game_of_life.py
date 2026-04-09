import numpy as np
import copy

class GameOfLife:
    def __init__(self, width=20, height=10):
        self.width = width
        self.height = height
        self.grid = self.initialize_grid()

    def initialize_grid(self):
        grid = np.random.choice([0, 1], size=(self.height, self.width), p=[0.5, 0.5]).astype(int)
        return grid

    def count_neighbors(self, row, col):
        neighbors = []
        for i in range(max(0, row-1), min(self.height, row+2)):
            for j in range(max(0, col-1), min(self.width, col+2)):
                if (i != row or j != col) and self.grid[i][j] == 1:
                    neighbors.append((i, j))
        return len(neighbors)

    def next_generation(self):
        new_grid = copy.deepcopy(self.grid)
        for i in range(self.height):
            for j in range(self.width):
                live_neighbors = self.count_neighbors(i, j)
                if self.grid[i][j] == 1:
                    if live_neighbors < 2 or live_neighbors > 3:
                        new_grid[i][j] = 0
                else:
                    if live_neighbors == 3:
                        new_grid[i][j] = 1
        self.grid = new_grid

    def print_grid(self):
        for row in self.grid:
            print(''.join(['*' if cell else ' ' for cell in row]))
        print()

    def run(self, generations=100):
        for _ in range(generations):
            self.print_grid()
            self.next_generation()

if __name__ == '__main__':
    game = GameOfLife()
    game.run(10)