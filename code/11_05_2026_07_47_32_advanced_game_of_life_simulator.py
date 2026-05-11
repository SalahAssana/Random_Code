import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d

class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.alive = False

class GameOfLife:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.cells = [[Cell(x, y) for y in range(height)] for x in range(width)]

    def print_board(self):
        plt.cla()
        ax = plt.axes(projection='3d')
        for row in self.cells:
            for cell in row:
                if cell.alive:
                    ax.scatter(cell.x, cell.y, 1, c='r', marker='o')
                else:
                    ax.scatter(cell.x, cell.y, 0.5, c='k', marker='x')
        plt.draw()
        plt.pause(0.01)

    def next_generation(self):
        new_cells = [[Cell(x, y) for y in range(self.height)] for x in range(self.width)]
        for row in self.cells:
            for cell in row:
                alive_neighbors = 0
                for dx in [-1, 0, 1]:
                    for dy in [-1, 0, 1]:
                        if abs(dx) + abs(dy) > 0:  # excluding the cell itself
                            nx = (cell.x + dx) % self.width
                            ny = (cell.y + dy) % self.height
                            if self.cells[nx][ny].alive:
                                alive_neighbors += 1
                if cell.alive and (alive_neighbors < 2 or alive_neighbors > 3):
                    new_cells[cell.x][cell.y] = Cell(cell.x, cell.y)
                    new_cells[cell.x][cell.y].alive = False
                elif not cell.alive and alive_neighbors == 3:
                    new_cells[cell.x][cell.y] = Cell(cell.x, cell.y)
                    new_cells[cell.x][cell.y].alive = True
        self.cells = new_cells

    def run(self, generations):
        for _ in range(generations):
            self.print_board()
            self.next_generation()

if __name__ == '__main__':
    game = GameOfLife(100, 100)
    game.run(1000)