from copy import deepcopy

class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.is_alive = False

    def is_alive(self):
        return self.is_alive

    def set_is_alive(self, value):
        self.is_alive = value


class Grid:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.cells = [[Cell(x, y) for y in range(height)] for x in range(width)]

    def get_cell(self, x, y):
        return self.cells[x][y]

    def set_is_alive(self, x, y, value):
        self.cells[x][y].set_is_alive(value)

    def next_generation(self):
        new_cells = [[Cell(x, y) for y in range(self.height)] for x in range(self.width)]
        for x in range(self.width):
            for y in range(self.height):
                live_neighbors = 0
                for dx in range(-1, 2):
                    for dy in range(-1, 2):
                        if (dx == 0 and dy == 0) or abs(dx) + abs(dy) > 1:
                            continue
                        nx, ny = x + dx, y + dy
                        if nx < 0 or nx >= self.width or ny < 0 or ny >= self.height:
                            continue
                        if self.get_cell(nx, ny).is_alive():
                            live_neighbors += 1
                new_cells[x][y].set_is_alive(self.get_cell(x, y).is_alive())
                if self.get_cell(x, y).is_alive() and (live_neighbors < 2 or live_neighbors > 3):
                    new_cells[x][y].set_is_alive(False)
                elif not self.get_cell(x, y).is_alive() and live_neighbors == 3:
                    new_cells[x][y].set_is_alive(True)
        return Grid(self.width, self.height), new_cells


def draw_grid(grid):
    for row in grid.cells:
        line = ''
        for cell in row:
            line += 'O' if cell.is_alive() else '.'
        print(line)


def main():
    grid = Grid(20, 10)
    grid.set_is_alive(1, 1, True)  # set the first cell to be alive
    for _ in range(100):
        old_grid, new_grid = grid.next_generation()
        draw_grid(old_grid)
        grid = new_grid


if __name__ == '__main__':
    main()