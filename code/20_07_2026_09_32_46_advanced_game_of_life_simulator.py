import numpy as np
import matplotlib.pyplot as plt
import time

class GameOfLife:
    def __init__(self, width=50, height=50):
        self.width = width
        self.height = height
        self.board = np.random.randint(0, 2, (height, width), dtype=int)

    def count_neighbors(self, x, y):
        neighbors = 0
        for i in range(-1, 2):
            for j in range(-1, 2):
                if not ((i == 0) and (j == 0)):
                    try:
                        neighbors += self.board[(y + j) % self.height, (x + i) % self.width]
                    except IndexError:
                        pass
        return neighbors

    def next_generation(self):
        new_board = np.copy(self.board)
        for x in range(self.width):
            for y in range(self.height):
                live_neighbors = self.count_neighbors(x, y)
                if self.board[y, x] == 1:  # Cell is alive
                    if (live_neighbors < 2) or (live_neighbors > 3):
                        new_board[y, x] = 0  # Underpopulation or Overpopulation
                else:  # Cell is dead
                    if live_neighbors == 3:
                        new_board[y, x] = 1  # Reproduction
        self.board = new_board

    def visualize(self):
        plt.ion()
        img = plt.imshow(self.board, cmap='gray', interpolation='none')
        plt.draw()
        plt.pause(0.05)

def main():
    game = GameOfLife()
    for _ in range(100):
        game.next_generation()
        game.visualize()

if __name__ == '__main__':
    main()