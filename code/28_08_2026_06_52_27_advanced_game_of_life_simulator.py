import random
import copy

class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.is_alive = True

class Grid:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.cells = [[Cell(x, y) for y in range(height)] for x in range(width)]

    def count_neighbors(self, cell):
        neighbors = 0
        for x in range(-1, 2):
            for y in range(-1, 2):
                if (x == 0 and y == 0): continue
                neighbor_x = cell.x + x
                neighbor_y = cell.y + y
                if (neighbor_x < 0 or neighbor_y < 0 or 
                    neighbor_x >= self.width or neighbor_y >= self.height): 
                    continue
                if (self.cells[neighbor_x][neighbor_y].is_alive):
                    neighbors += 1
        return neighbors

    def next_generation(self):
        new_grid = copy.deepcopy(self)
        for cell in new_grid.cells:
            for c in cell:
                live_neighbors = self.count_neighbors(c)
                if ((c.is_alive and (live_neighbors < 2 or live_neighbors > 3)) 
                    or (not c.is_alive and live_neighbors == 3)):
                    c.is_alive = False
                else:
                    c.is_alive = True
        return new_grid

    def print_grid(self):
        for row in self.cells:
            for cell in row:
                if cell.is_alive: 
                    print('*', end=' ')
                else: 
                    print(' ', end=' ')
            print()

def main():
    width = 20
    height = 10
    grid = Grid(width, height)
    
    # initialize some cells to be alive
    for x in range(5):
        for y in range(height // 2):
            if random.random() < 0.3:
                grid.cells[x][y].is_alive = True
    
    for _ in range(10):  # run the simulation for 10 generations
        print("Generation", _, ":")
        grid.print_grid()
        grid = grid.next_generation()
    print()

if __name__ == '__main__':
    main()