import random
from heapq import heappop, heappush

class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.visited = False
        self.parent = None
        self.g = float('inf')
        self.h = 0
        self.f = float('inf')

class Maze:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.cells = [[Cell(x, y) for y in range(height)] for x in range(width)]
        self.start = None
        self.end = None

    def generate_maze(self):
        stack = []
        current_cell = random.choice([cell for row in self.cells for cell in row])
        while True:
            neighbors = [(x, y) for (x, y), c in enumerate([[row[y] for row in self.cells]) if c.x == current_cell.x and abs(c.y - y) <= 1]
            unvisited_neighbors = [neighbor for neighbor in neighbors if not [cell.visited for cell_row in self.cells for cell in cell_row if cell.x == neighbor[0] and cell.y == neighbor[1]]]
            if len(unvisited_neighbors):
                next_cell = random.choice(unvisited_neighbors)
                self._mark_path(current_cell, next_cell)
                stack.append(next_cell)
                current_cell = next_cell
            else:
                if not stack:
                    break
                current_cell = stack.pop()

    def _mark_path(self, start, end):
        while True:
            if start == end:
                return
            if start.parent is None:
                return
            start.visited = True
            start = start.parent

    def a_star_search(self, start, end):
        open_list = [(0, start)]
        came_from = {}
        g_score = {cell: float('inf') for row in self.cells for cell in row}
        g_score[start] = 0
        while True:
            if not open_list:
                return None
            _, current_cell = heappop(open_list)
            if current_cell == end:
                path = [current_cell]
                while True:
                    if path[-1].parent is None:
                        break
                    path.append(path[-1].parent)
                return path[::-1]
            for neighbor in [(x, y) for (x, y), c in enumerate([[row[y] for row in self.cells]) if c.x == current_cell.x and abs(c.y - y) <= 1]:
                neighbor_cell = self.cells[neighbor[0]][neighbor[1]]
                tentative_g_score = g_score[current_cell] + 1
                if tentative_g_score < g_score[neighbor_cell]:
                    came_from[neighbor_cell] = current_cell
                    g_score[neighbor_cell] = tentative_g_score
                    heappush(open_list, (tentative_g_score, neighbor_cell))

    def generate_maze_a_star(self):
        self.generate_maze()
        start = random.choice([cell for row in self.cells for cell in row])
        end = random.choice([cell for row in self.cells for cell in row])
        while True:
            path = self.a_star_search(start, end)
            if path is not None:
                break
        return path

    def print_maze(self):
        for y in range(self.height):
            for x in range(self.width):
                cell = self.cells[x][y]
                if cell.visited and cell != self.end:
                    print('#', end=' ')
                elif cell == self.end:
                    print('E', end=' ')
                else:
                    print('#' if (x, y) == self.start or not [cell.visited for row in self.cells for cell in row] else ' ', end=' ')
            print()

if __name__ == '__main__':
    maze = Maze(21, 11)
    maze.generate_maze_a_star()
    maze.print_maze()