# Game of Life Simulator
import random
import time

class Cell:
    def __init__(self):
        self.alive = False

    def is_alive(self):
        return self.alive

    def set_alive(self):
        self.alive = True

    def set_dead(self):
        self.alive = False


class GameOfLife:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.grid = [[Cell() for _ in range(width)] for _ in range(height)]

    def randomize_grid(self):
        for i in range(self.height):
            for j in range(self.width):
                if random.random() < 0.5:
                    self.grid[i][j].set_alive()
                else:
                    self.grid[i][j].set_dead()

    def print_grid(self):
        for row in self.grid:
            for cell in row:
                if cell.is_alive():
                    print('*', end=' ')
                else:
                    print(' ', end=' ')
            print()

    def next_generation(self):
        new_grid = [[Cell() for _ in range(self.width)] for _ in range(self.height)]

        for i in range(self.height):
            for j in range(self.width):
                alive_neighbors = 0
                for x in range(-1, 2):
                    for y in range(-1, 2):
                        if (x == 0 and y == 0) or i + x < 0 or i + x >= self.height or j + y < 0 or j + y >= self.width:
                            continue
                        if self.grid[i + x][j + y].is_alive():
                            alive_neighbors += 1

                if self.grid[i][j].is_alive() and (alive_neighbors < 2 or alive_neighbors > 3):
                    new_grid[i][j].set_dead()
                elif not self.grid[i][j].is_alive() and alive_neighbors == 3:
                    new_grid[i][j].set_alive()
                else:
                    new_grid[i][j] = self.grid[i][j]

        self.grid = new_grid


if __name__ == '__main__':
    game = GameOfLife(20, 20)
    game.randomize_grid()

    for _ in range(10):
        game.print_grid()
        time.sleep(1)
        game.next_generation()