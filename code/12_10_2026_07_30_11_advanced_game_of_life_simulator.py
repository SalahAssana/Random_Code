import threading
from queue import Queue
import numpy as np
import time

class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.alive = False
        self.lock = threading.Lock()

    def is_alive(self):
        with self.lock:
            return self.alive

    def set_alive(self):
        with self.lock:
            self.alive = True

    def set_dead(self):
        with self.lock:
            self.alive = False

class Grid:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.cells = [[Cell(x, y) for y in range(height)] for x in range(width)]
        self.next_generation_queue = Queue()

    def get_cell(self, x, y):
        return self.cells[x][y]

    def set_cell_alive(self, x, y):
        self.get_cell(x, y).set_alive()

    def set_cell_dead(self, x, y):
        self.get_cell(x, y).set_dead()

    def check_neighbors(self, cell):
        alive_neighbors = 0
        for dx in range(-1, 2):
            for dy in range(-1, 2):
                if (dx == 0 and dy == 0) or abs(dx) + abs(dy) > 1:
                    continue
                nx = cell.x + dx
                ny = cell.y + dy
                if nx < 0 or ny < 0 or nx >= self.width or ny >= self.height:
                    continue
                if cell.x == nx and cell.y == ny:
                    continue
                if cell.get_cell(nx, ny).is_alive():
                    alive_neighbors += 1
        return alive_neighbors

    def next_generation(self):
        new_grid = [[Cell(x, y) for y in range(self.height)] for x in range(self.width)]
        for x in range(self.width):
            for y in range(self.height):
                cell = self.get_cell(x, y)
                if cell.is_alive():
                    alive_neighbors = self.check_neighbors(cell)
                    if (alive_neighbors < 2 or alive_neighbors > 3):
                        new_grid[x][y].set_dead()
                    else:
                        new_grid[x][y].set_alive()
                else:
                    alive_neighbors = self.check_neighbors(cell)
                    if alive_neighbors == 3:
                        new_grid[x][y].set_alive()
        return new_grid

    def update(self):
        while not self.next_generation_queue.empty():
            grid = self.next_generation_queue.get()
            for x in range(self.width):
                for y in range(self.height):
                    cell = grid[x][y]
                    if cell.is_alive():
                        if np.random.rand() < 0.1:
                            cell.set_dead()
                    else:
                        if np.random.rand() < 0.2:
                            cell.set_alive()
            self.next_generation_queue.put(grid)

    def run(self, iterations):
        for _ in range(iterations):
            new_grid = self.next_generation()
            self.cells = new_grid
            time.sleep(1)
            print(np.array([[cell.is_alive() for cell in row] for row in self.cells]))

if __name__ == '__main__':
    grid = Grid(10, 10)
    grid.run(1000)