import random
from collections import deque

class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.alive = random.choice([True, False])

    def update(self, neighbors):
        if self.alive:
            if len([neighbor for neighbor in neighbors if neighbor.alive]) < 2 and len([neighbor for neighbor in neighbors if neighbor.alive]) > 3:
                return False
            elif len([neighbor for neighbor in neighbors if neighbor.alive]) == 2 or len([neighbor for neighbor in neighbors if neighbor.alive]) == 3:
                return True
        else:
            if len([neighbor for neighbor in neighbors if neighbor.alive]) == 3:
                return True
            else:
                return False

class Grid:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.cells = [[Cell(x, y) for y in range(height)] for x in range(width)]

    def update(self):
        new_grid = [[Cell(x, y) for y in range(self.height)] for x in range(self.width)]
        for row in range(self.height):
            for col in range(self.width):
                cell = self.cells[col][row]
                neighbors = deque()
                if col > 0:
                    neighbors.append(self.cells[col-1][row])
                if col < self.width - 1:
                    neighbors.append(self.cells[col+1][row])
                if row > 0:
                    neighbors.append(self.cells[col][row-1])
                if row < self.height - 1:
                    neighbors.append(self.cells[col][row+1])
                if col > 0 and row > 0:
                    neighbors.append(self.cells[col-1][row-1])
                if col < self.width - 1 and row > 0:
                    neighbors.append(self.cells[col+1][row-1])
                if col > 0 and row < self.height - 1:
                    neighbors.append(self.cells[col-1][row+1])
                if col < self.width - 1 and row < self.height - 1:
                    neighbors.append(self.cells[col+1][row+1])
                if col == 0:
                    if row > 0:
                        neighbors.append(self.cells[0][row-1])
                    if row < self.height - 1:
                        neighbors.append(self.cells[0][row+1])
                elif col == self.width - 1:
                    if row > 0:
                        neighbors.append(self.cells[self.width-1][row-1])
                    if row < self.height - 1:
                        neighbors.append(self.cells[self.width-1][row+1])
                cell.alive = cell.update(neighbors)
                new_grid[col][row] = cell
        return Grid(self.width, self.height)

    def print_grid(self):
        for row in self.cells:
            for cell in row:
                if cell.alive:
                    print('O', end=' ')
                else:
                    print('.', end=' ')
            print()

if __name__ == '__main__':
    width = 10
    height = 10
    grid = Grid(width, height)
    iterations = 100
    for _ in range(iterations):
        grid = grid.update()
    grid.print_grid()