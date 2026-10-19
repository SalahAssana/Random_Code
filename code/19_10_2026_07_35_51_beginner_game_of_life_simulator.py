# Game of Life Simulator

import random
import time

# Define constants
WIDTH = 20
HEIGHT = 10

# Initialize grid with random values
grid = [[random.randint(0, 1) for _ in range(WIDTH)] for _ in range(HEIGHT)]

def print_grid():
    # Print grid to console
    for row in grid:
        print(" ".join(str(cell) for cell in row))

def count_neighbors(x, y):
    # Count number of live neighbors
    count = 0
    for i in range(-1, 2):
        for j in range(-1, 2):
            if (i == 0 and j == 0): continue
            nx, ny = x + i, y + j
            if (nx >= 0 and nx < HEIGHT and ny >= 0 and ny < WIDTH and grid[ny][nx] == 1):
                count += 1
    return count

def next_generation():
    # Create new grid with updated values
    new_grid = [[0 for _ in range(WIDTH)] for _ in range(HEIGHT)]
    for y in range(HEIGHT):
        for x in range(WIDTH):
            live_neighbors = count_neighbors(x, y)
            if (grid[y][x] == 1 and (live_neighbors < 2 or live_neighbors > 3)):
                new_grid[y][x] = 0
            elif (grid[y][x] == 0 and live_neighbors == 3):
                new_grid[y][x] = 1
            else:
                new_grid[y][x] = grid[y][x]
    return new_grid

if __name__ == '__main__':
    # Main loop
    while True:
        print_grid()
        time.sleep(0.5)
        global grid
        grid = next_generation()