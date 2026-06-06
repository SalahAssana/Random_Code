import numpy as np
from matplotlib import animation, pyplot as plt
from numba import njit

class Grid:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.state = np.random.choice([0, 1], size=(height, width), p=[0.5, 0.5]).astype(bool)

    def get_neighbors(self, x, y):
        neighbors = []
        for dx in range(-1, 2):
            for dy in range(-1, 2):
                if abs(dx) + abs(dy) == 1: continue
                nx, ny = (x + dx) % self.width, (y + dy) % self.height
                neighbors.append((nx, ny))
        return neighbors

    def count_neighbors(self, x, y):
        return sum(1 for nx, ny in self.get_neighbors(x, y) if self.state[ny, nx])

    def next_generation(self):
        new_state = np.zeros_like(self.state)
        for i in range(self.height):
            for j in range(self.width):
                live_neighbors = self.count_neighbors(j, i)
                if self.state[i, j]:
                    new_state[i, j] = (live_neighbors == 2 or live_neighbors == 3)
                else:
                    new_state[i, j] = (live_neighbors == 3)
        return new_state

    def draw(self):
        plt.imshow(self.state, cmap='gray', interpolation='nearest')
        plt.axis('off')

def game_of_life(grid, num_generations):
    frames = []
    for _ in range(num_generations):
        grid.state = grid.next_generation()
        frames.append([grid.draw()])
    return animation.ArtistArray(frames)

if __name__ == '__main__':
    grid = Grid(100, 100)
    ani = game_of_life(grid, 50)
    plt.show()