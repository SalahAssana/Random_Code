import random
import copy
import time
import keyboard

class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.alive = False

    def is_alive(self):
        return self.alive

    def set_alive(self):
        self.alive = True

    def set_dead(self):
        self.alive = False


class Grid:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.cells = [[Cell(x, y) for y in range(height)] for x in range(width)]

    def get_cell(self, x, y):
        return self.cells[x][y]

    def set_cell_alive(self, x, y):
        self.cells[x][y].set_alive()

    def set_cell_dead(self, x, y):
        self.cells[x][y].set_dead()

    def count_alive_neighbors(self, cell):
        neighbors = 0
        for dx in range(-1, 2):
            for dy in range(-1, 2):
                if abs(dx) + abs(dy) == 1:  # skip self
                    continue
                nx, ny = cell.x + dx, cell.y + dy
                if 0 <= nx < self.width and 0 <= ny < self.height:
                    neighbors += int(self.get_cell(nx, ny).is_alive())
        return neighbors

    def next_generation(self):
        new_cells = copy.deepcopy(self.cells)
        for x in range(self.width):
            for y in range(self.height):
                cell = self.get_cell(x, y)
                alive_neighbors = self.count_alive_neighbors(cell)
                if cell.is_alive():
                    if alive_neighbors < 2 or alive_neighbors > 3:
                        new_cells[x][y].set_dead()
                else:
                    if alive_neighbors == 3:
                        new_cells[x][y].set_alive()
        self.cells = new_cells


def print_grid(grid):
    for y in range(grid.height):
        for x in range(grid.width):
            cell = grid.get_cell(x, y)
            if cell.is_alive():
                print('*', end=' ')
            else:
                print(' ', end=' ')
        print()


def main():
    width = 100
    height = 100
    grid = Grid(width, height)

    for x in range(width):
        for y in range(height):
            if random.random() < 0.5:  # 50% chance of being alive at start
                grid.set_cell_alive(x, y)

    while True:
        print_grid(grid)
        input("Press Enter to step... ")
        grid.next_generation()
        time.sleep(1)  # pause for a moment

if __name__ == '__main__':
    main()

while True:
    if keyboard.is_pressed('esc'):
        break