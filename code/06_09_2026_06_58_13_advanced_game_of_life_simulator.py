import random
from copy import deepcopy

class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.alive = random.choice([True, False])

    def __str__(self):
        return f"Cell({self.x}, {self.y}): {'Alive' if self.alive else 'Dead'}"

class Grid:
    def __init__(self, width=20, height=10):
        self.width = width
        self.height = height
        self.cells = [[Cell(x, y) for y in range(height)] for x in range(width)]

    def __str__(self):
        result = ""
        for row in self.cells:
            for cell in row:
                result += str(cell) + "\n"
            result += "\n"
        return result

    def count_neighbors(self, cell):
        neighbors = 0
        for x in range(-1, 2):
            for y in range(-1, 2):
                if (x == 0 and y == 0) or not ((0 <= cell.x + x < self.width) and (0 <= cell.y + y < self.height)):
                    continue
                neighbors += int(self.cells[cell.x + x][cell.y + y].alive)
        return neighbors

    def next_generation(self):
        new_grid = Grid()
        for x in range(self.width):
            for y in range(self.height):
                cell = self.cells[x][y]
                alive_neighbors = self.count_neighbors(cell)
                if cell.alive:
                    new_grid.cells[x][y].alive = (alive_neighbors == 2 or alive_neighbors == 3)
                else:
                    new_grid.cells[x][y].alive = (alive_neighbors == 3)
        return new_grid

def main():
    grid = Grid()
    print(grid)

    for _ in range(10):
        grid = grid.next_generation()
        print(grid)

if __name__ == '__main__':
    main()