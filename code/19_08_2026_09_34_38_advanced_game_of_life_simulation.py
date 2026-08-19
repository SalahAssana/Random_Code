#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import random

class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.alive = False

class GameOfLife:
    def __init__(self, width=20, height=20):
        self.width = width
        self.height = height
        self.cells = [[Cell(x, y) for y in range(height)] for x in range(width)]

    def count_neighbors(self, cell):
        neighbors = 0
        for dx in range(-1, 2):
            for dy in range(-1, 2):
                if (dx == 0 and dy == 0):
                    continue
                nx, ny = cell.x + dx, cell.y + dy
                if (nx < 0 or nx >= self.width or ny < 0 or ny >= self.height):
                    continue
                if (self.cells[nx][ny].alive):
                    neighbors += 1
        return neighbors

    def step(self):
        new_cells = [[Cell(x, y) for y in range(self.height)] for x in range(self.width)]
        for cell in [cell for row in self.cells for cell in row]:
            live_neighbors = self.count_neighbors(cell)
            if (cell.alive and (live_neighbors < 2 or live_neighbors > 3)):
                new_cells[cell.x][cell.y].alive = False
            elif (not cell.alive and live_neighbors == 3):
                new_cells[cell.x][cell.y].alive = True
        self.cells = new_cells

    def print_state(self):
        for row in self.cells:
            for cell in row:
                if (cell.alive):
                    print("*", end=" ")
                else:
                    print(" ", end=" ")
            print()

if __name__ == '__main__':
    game = GameOfLife()
    for _ in range(1000):  # run for 1000 steps
        game.print_state()
        game.step()