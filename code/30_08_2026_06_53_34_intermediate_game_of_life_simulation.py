#!/usr/bin/env python3
# coding=utf8

import random

class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.is_alive = False

class GameOfLife:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.cells = [[Cell(x, y) for y in range(height)] for x in range(width)]

    def generate_random_cells(self, proportion):
        for cell in [cell for row in self.cells for cell in row]:
            if random.random() < proportion:
                cell.is_alive = True

    def get_neighbors(self, cell):
        neighbors = []
        for dx in [-1, 0, 1]:
            for dy in [-1, 0, 1]:
                if (dx == 0 and dy == 0) or abs(dx) + abs(dy) > 1:
                    continue
                x, y = cell.x + dx, cell.y + dy
                if 0 <= x < self.width and 0 <= y < self.height:
                    neighbors.append(self.cells[x][y])
        return neighbors

    def count_alive_neighbors(self, cell):
        return sum(1 for neighbor in self.get_neighbors(cell) if neighbor.is_alive)

    def evolve(self):
        new_cells = [[Cell(x, y) for y in range(self.height)] for x in range(self.width)]
        for cell in [cell for row in self.cells for cell in row]:
            alive_neighbors = self.count_alive_neighbors(cell)
            if cell.is_alive:
                if alive_neighbors < 2 or alive_neighbors > 3:
                    new_cells[cell.x][cell.y].is_alive = False
                else:
                    new_cells[cell.x][cell.y].is_alive = True
            else:
                if alive_neighbors == 3:
                    new_cells[cell.x][cell.y].is_alive = True
        self.cells = new_cells

    def print_game(self):
        for row in self.cells:
            print(' '.join(['*' if cell.is_alive else ' ' for cell in row]))

if __name__ == '__main__':
    game = GameOfLife(20, 20)
    game.generate_random_cells(0.5)
    for _ in range(100):
        game.evolve()
        game.print_game()