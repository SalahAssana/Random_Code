import numpy as np
from collections import deque

class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.is_alive = False

class GameOfLife:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.cells = [[Cell(x, y) for y in range(height)] for x in range(width)]

    def generate_initial_state(self):
        # Initialize the game with random initial state
        np.random.seed(0)
        self.is_alive = (np.random.rand(self.width, self.height) < 0.5).astype(bool)

    def count_neighbors(self, cell):
        x, y = cell.x, cell.y
        neighbors = []
        for dx in [-1, 0, 1]:
            for dy in [-1, 0, 1]:
                if dx == 0 and dy == 0:
                    continue
                nx, ny = x + dx, y + dy
                if 0 <= nx < self.width and 0 <= ny < self.height:
                    neighbors.append(self.cells[nx][ny])
        return len([neighbor for neighbor in neighbors if neighbor.is_alive])

    def next_generation(self):
        # Create a copy of the current state
        new_state = [[Cell(x, y) for y in range(self.height)] for x in range(self.width)]
        for cell in self.cells:
            live_neighbors = self.count_neighbors(cell)
            if cell.is_alive and (live_neighbors < 2 or live_neighbors > 3):
                new_state[cell.x][cell.y].is_alive = False
            elif not cell.is_alive and live_neighbors == 3:
                new_state[cell.x][cell.y].is_alive = True
        self.cells = new_state

    def print_game(self):
        for row in self.cells:
            print(' '.join(['*' if cell.is_alive else ' ' for cell in row]))

if __name__ == '__main__':
    game = GameOfLife(20, 20)
    game.generate_initial_state()
    for i in range(10):
        game.print_game()
        game.next_generation()