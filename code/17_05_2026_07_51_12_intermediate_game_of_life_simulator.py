import numpy as np

class GameOfLife:
    def __init__(self, width: int, height: int):
        self.width = width
        self.height = height
        self.grid = np.zeros((height, width), dtype=int)

    def set_cell(self, x: int, y: int, state: int):
        if 0 <= x < self.width and 0 <= y < self.height:
            self.grid[y][x] = state
        else:
            raise ValueError("Cell out of bounds")

    def get_cell(self, x: int, y: int) -> int:
        if 0 <= x < self.width and 0 <= y < self.height:
            return self.grid[y][x]
        else:
            raise ValueError("Cell out of bounds")

    def count_neighbors(self, x: int, y: int) -> int:
        neighbors = 0
        for i in range(-1, 2):
            for j in range(-1, 2):
                if i == 0 and j == 0:
                    continue
                nx, ny = x + i, y + j
                if 0 <= nx < self.width and 0 <= ny < self.height:
                    neighbors += int(self.grid[ny][nx])
        return neighbors

    def next_generation(self):
        new_grid = np.zeros((self.height, self.width), dtype=int)
        for y in range(self.height):
            for x in range(self.width):
                cell_state = self.grid[y][x]
                live_neighbors = self.count_neighbors(x, y)
                if cell_state == 1:
                    new_grid[y][x] = 1 if (live_neighbors == 2 or live_neighbors == 3) else 0
                else:
                    new_grid[y][x] = 1 if live_neighbors == 3 else 0
        self.grid = new_grid

    def print_grid(self):
        for y in range(self.height):
            for x in range(self.width):
                print(" " if self.grid[y][x] == 0 else "#", end="")
            print()

def main():
    game = GameOfLife(20, 20)
    # Initialize the grid with some cells
    game.set_cell(5, 5, 1)
    game.set_cell(6, 6, 1)
    game.set_cell(7, 7, 1)
    game.set_cell(8, 8, 1)

    for _ in range(10):
        print("Generation:")
        game.print_grid()
        game.next_generation()

if __name__ == '__main__':
    main()