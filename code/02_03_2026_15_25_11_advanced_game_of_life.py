class Cell:
    def __init__(self):
        self.alive = False

    def is_alive(self):
        return self.alive

    def set_alive(self, value):
        self.alive = value


class Grid:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.cells = [[Cell() for _ in range(width)] for _ in range(height)]

    def get_cell(self, x, y):
        return self.cells[y][x]

    def set_cell_alive(self, x, y, value):
        self.get_cell(x, y).set_alive(value)

    def count_neighbors(self, x, y):
        neighbors = 0
        for dx in range(-1, 2):
            for dy in range(-1, 2):
                if (dx == 0 and dy == 0) or abs(dx) + abs(dy) > 1:
                    continue
                nx, ny = x + dx, y + dy
                if nx < 0 or ny < 0 or nx >= self.width or ny >= self.height:
                    continue
                if self.get_cell(nx, ny).is_alive():
                    neighbors += 1
        return neighbors

    def step(self):
        new_grid = [[Cell() for _ in range(self.width)] for _ in range(self.height)]
        for x in range(self.width):
            for y in range(self.height):
                cell = self.get_cell(x, y)
                alive_neighbors = self.count_neighbors(x, y)
                if cell.is_alive():
                    if alive_neighbors in [2, 3]:
                        new_grid[y][x].set_alive(True)
                    else:
                        new_grid[y][x].set_alive(False)
                elif alive_neighbors == 3:
                    new_grid[y][x].set_alive(True)
        self.cells = new_grid


def main():
    if __name__ == '__main__':
        grid = Grid(20, 20)
        for x in range(grid.width):
            for y in range(grid.height):
                if random.randint(0, 1):
                    grid.set_cell_alive(x, y, True)
        for _ in range(100):
            print("\033[H\033[2J")  # Clear screen
            for y in range(grid.height):
                for x in range(grid.width):
                    cell = grid.get_cell(x, y)
                    if cell.is_alive():
                        print("*", end=" ")
                    else:
                        print(" ", end=" ")
                print()
            grid.step()
        input("Press Enter to exit.")


import random
if __name__ == '__main__':
    main()