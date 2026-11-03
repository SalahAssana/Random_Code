import numpy as np
from joblib import Parallel, delayed

class GameOfLife:
    def __init__(self, width: int, height: int):
        self.width = width
        self.height = height
        self.grid = np.random.randint(0, 2, (height, width), dtype=bool)

    def count_neighbors(self, x: int, y: int) -> int:
        neighbors = 0
        for i in range(-1, 2):
            for j in range(-1, 2):
                if not ((i == 0 and j == 0) or i < 0 or j < 0 or i >= self.height or j >= self.width):
                    neighbors += int(self.grid[x + i][y + j])
        return neighbors

    def next_generation(self) -> None:
        new_grid = np.zeros((self.height, self.width), dtype=bool)
        for x in range(self.height):
            for y in range(self.width):
                live_neighbors = self.count_neighbors(x, y)
                if self.grid[x][y]:
                    new_grid[x][y] = (live_neighbors == 2 or live_neighbors == 3)
                else:
                    new_grid[x][y] = (live_neighbors == 3)
        self.grid = new_grid

    def run(self, generations: int) -> None:
        for _ in range(generations):
            Parallel(n_jobs=-1)(delayed(self.next_generation)() for _ in range(1000))

# Test the code
if __name__ == '__main__':
    game = GameOfLife(50, 50)
    game.run(10)