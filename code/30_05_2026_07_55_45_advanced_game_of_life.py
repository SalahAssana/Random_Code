import random
import copy

class GameOfLife:
    def __init__(self, width=20, height=10):
        self.width = width
        self.height = height
        self.board = [[random.choice([0, 1]) for _ in range(width)] for _ in range(height)]

    def count_neighbors(self, x, y):
        neighbors = 0
        for i in range(-1, 2):
            for j in range(-1, 2):
                if i == 0 and j == 0:
                    continue
                nx, ny = x + i, y + j
                if 0 <= nx < self.width and 0 <= ny < self.height:
                    neighbors += self.board[ny][nx]
        return neighbors

    def next_generation(self):
        new_board = [[copy.deepcopy(cell) for _ in range(self.width)] for _ in range(self.height)]
        for y in range(self.height):
            for x in range(self.width):
                live_neighbors = self.count_neighbors(x, y)
                if self.board[y][x] == 1:
                    if live_neighbors < 2 or live_neighbors > 3:
                        new_board[y][x] = 0
                    else:
                        new_board[y][x] = 1
                else:
                    if live_neighbors == 3:
                        new_board[y][x] = 1
            self.board = copy.deepcopy(new_board)

    def print_board(self):
        for row in self.board:
            print(' '.join(['*' if cell else ' ' for cell in row]))
        print()

def main():
    game = GameOfLife()
    for _ in range(10):
        game.print_board()
        game.next_generation()

if __name__ == '__main__':
    main()