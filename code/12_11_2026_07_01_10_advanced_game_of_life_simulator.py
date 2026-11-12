class Cell:
    def __init__(self, state):
        self.state = state

    def is_alive(self):
        return self.state == 1

    def toggle_state(self):
        self.state = 1 - self.state


class Grid:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.cells = [[Cell(random.randint(0, 1)) for _ in range(width)] for _ in range(height)]

    def print_grid(self):
        for row in self.cells:
            for cell in row:
                print("1" if cell.is_alive() else "0", end=" ")
            print()

    def next_generation(self):
        new_cells = [[Cell(0) for _ in range(self.width)] for _ in range(self.height)]
        for i in range(self.height):
            for j in range(self.width):
                live_neighbors = self.count_live_neighbors(i, j)
                if self.cells[i][j].is_alive():
                    if live_neighbors < 2 or live_neighbors > 3:
                        new_cells[i][j] = Cell(0)
                    else:
                        new_cells[i][j] = Cell(1)
                else:
                    if live_neighbors == 3:
                        new_cells[i][j] = Cell(1)
            self.cells = new_cells


    def count_live_neighbors(self, i, j):
        count = 0
        for x in range(max(0, i-1), min(self.height, i+2)):
            for y in range(max(0, j-1), min(self.width, j+2)):
                if (x != i or y != j) and self.cells[x][y].is_alive():
                    count += 1
        return count


import random

if __name__ == '__main__':
    width = int(input("Enter grid width: "))
    height = int(input("Enter grid height: "))
    game_of_life = Grid(width, height)
    game_of_life.print_grid()
    for _ in range(10):
        game_of_life.next_generation()
        print("\n")
        game_of_life.print_grid()