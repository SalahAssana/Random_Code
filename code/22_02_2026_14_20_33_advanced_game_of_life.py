import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.state = 0  # 0: dead, 1: alive

class Grid:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.cells = [[Cell(x, y) for y in range(height)] for x in range(width)]

    def get_cell(self, x, y):
        return self.cells[x][y]

    def set_cell_state(self, x, y, state):
        self.get_cell(x, y).state = state

    def count_live_neighbors(self, x, y):
        count = 0
        for i in range(max(0, x-1), min(self.width, x+2)):
            for j in range(max(0, y-1), min(self.height, y+2)):
                if (i, j) != (x, y) and self.get_cell(i, j).state == 1:
                    count += 1
        return count

    def next_generation(self):
        new_grid = Grid(self.width, self.height)
        for x in range(self.width):
            for y in range(self.height):
                live_neighbors = self.count_live_neighbors(x, y)
                if self.get_cell(x, y).state == 1:
                    new_grid.set_cell_state(x, y, 0) if live_neighbors < 2 or live_neighbors > 3 else 1
                else:
                    new_grid.set_cell_state(x, y, 1) if live_neighbors == 3 else 0
        return new_grid

    def print_grid(self):
        for x in range(self.width):
            for y in range(self.height):
                cell = self.get_cell(x, y)
                if cell.state:
                    print('X', end=' ')
                else:
                    print('.', end=' ')
            print()

def main():
    # Create a 10x10 grid with some initial cells
    grid = Grid(10, 10)
    for x in range(5):
        for y in range(5):
            grid.set_cell_state(x, y, 1)

    # Evolve the grid over several generations
    for _ in range(20):
        print("Generation:")
        grid.print_grid()
        grid = grid.next_generation()

if __name__ == '__main__':
    main()