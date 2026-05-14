import random
from collections import defaultdict

class WordSearch:
    def __init__(self, words, size):
        self.words = words
        self.size = size
        self.board = [[random.choice('abcdefghijklmnopqrstuvwxyz') for _ in range(size)] for _ in range(size)]
        self.directions = [(0, 1), (0, -1), (1, 0), (-1, 0), (1, 1), (-1, -1), (1, -1), (-1, 1)]

    def place_word(self, word):
        for direction in self.directions:
            if self._is_valid_place(word, direction):
                self._place_word(word, direction)
                return

    def _is_valid_place(self, word, direction):
        x0, y0 = random.randint(0, self.size - 1), random.randint(0, self.size - len(word))
        for i, char in enumerate(word):
            x, y = x0 + i * direction[0], y0 + i * direction[1]
            if (x < 0 or x >= self.size or y < 0 or y >= self.size) or self.board[x][y] != char:
                return False
        return True

    def _place_word(self, word, direction):
        x0, y0 = random.randint(0, self.size - 1), random.randint(0, self.size - len(word))
        for i, char in enumerate(word):
            x, y = x0 + i * direction[0], y0 + i * direction[1]
            self.board[x][y] = char

    def generate_hints(self):
        return {word: [(x, y) for i, (x, y) in enumerate([(i // len(word), i % len(word))) for word in self.words])}

    def score_board(self):
        return sum(1 for row in self.board for cell in row if cell.isalpha())

if __name__ == '__main__':
    words = ['apple', 'banana', 'orange']
    size = 10
    search = WordSearch(words, size)
    search.place_word('apple')
    print(search.board)
    hints = search.generate_hints()
    for word, hint in hints.items():
        print(f"{word}: {hint}")
    score = search.score_board()
    print(f"Score: {score}")