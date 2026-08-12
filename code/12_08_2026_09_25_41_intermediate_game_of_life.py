import numpy as np
import time

class GameOfLife:
    def __init__(self, width=20, height=10):
        self.width = width
        self.height = height
        self.board = np.random.choice([0, 1], size=(height, width), p=[0.5, 0.5]).astype(int)

    def print_board(self):
        for row in self.board:
            print(' '.join(['*' if cell else ' ' for cell in row]))

    def count_neighbors(self, x, y):
        neighbors = []
        for i in range(-1, 2):
            for j in range(-1, 2):
                if not (i == 0 and j == 0) and 0 <= x + i < self.height and 0 <= y + j < self.width:
                    neighbors.append(self.board[x + i][y + j])
        return sum(neighbors)

    def next_generation(self):
        new_board = np.zeros((self.height, self.width), dtype=int)
        for x in range(self.height):
            for y in range(self.width):
                live_neighbors = self.count_neighbors(x, y)
                if self.board[x][y] == 1 and (live_neighbors < 2 or live_neighbors > 3):
                    new_board[x][y] = 0
                elif self.board[x][y] == 0 and live_neighbors == 3:
                    new_board[x][y] = 1
                else:
                    new_board[x][y] = self.board[x][y]
        self.board = new_board

    def run(self, generations):
        for _ in range(generations):
            self.print_board()
            time.sleep(0.5)
            self.next_generation()

if __name__ == '__main__':
    game = GameOfLife()
    game.run(10)