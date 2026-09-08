from random import randint
import copy

class Cell:
    def __init__(self):
        self.is_alive = False

class Grid:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.cells = [[Cell() for _ in range(width)] for _ in range(height)]

    def print_grid(self):
        for row in self.cells:
            for cell in row:
                if cell.is_alive:
                    print('*', end=' ')
                else:
                    print(' ', end=' ')
            print()

    def count_neighbors(self, x, y):
        neighbors = 0
        for i in range(-1, 2):
            for j in range(-1, 2):
                if (i == 0 and j == 0) or not (0 <= x + i < self.width and 0 <= y + j < self.height):
                    continue
                if self.cells[y + j][x + i].is_alive:
                    neighbors += 1
        return neighbors

    def update(self):
        new_grid = copy.deepcopy(self)
        for y in range(self.height):
            for x in range(self.width):
                current_cell = self.cells[y][x]
                live_neighbors = self.count_neighbors(x, y)
                if current_cell.is_alive:
                    if live_neighbors < 2 or live_neighbors > 3:
                        new_grid.cells[y][x].is_alive = False
                else:
                    if live_neighbors == 3:
                        new_grid.cells[y][x].is_alive = True
        return new_grid

    def randomize(self):
        for y in range(self.height):
            for x in range(self.width):
                self.cells[y][x].is_alive = (randint(0, 1) == 1)

if __name__ == '__main__':
    grid = Grid(20, 20)
    grid.randomize()
    generations = 100
    for _ in range(generations):
        print("Generation", _ + 1)
        grid.print_grid()
        grid = grid.update()