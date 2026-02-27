import random

class ChessGame:
    def __init__(self):
        self.board = [[' ' for _ in range(8)] for _ in range(8)]
        self.turn = 'white'

    def print_board(self):
        print('  a b c d e f g h')
        for i, row in enumerate(self.board):
            print(i + 1, end=' ')
            for piece in row:
                print(piece.ljust(2), end='')
            print()

    def is_valid_move(self, start, end):
        if self.turn != 'white':
            return False
        if self.board[start[0]][start[1]] == ' ' or self.board[end[0]][end[1]] == ' ':
            return False
        # check piece type and movement rules
        # ...

    def minimax(self, depth, alpha, beta, maximizing):
        if depth == 0:
            return 0

        scores = []
        for move in self.get_moves():
            self.make_move(move)
            score = -self.minimax(depth-1, -beta, -alpha, not maximizing) if maximizing else self.minimax(depth-1, alpha, beta, not maximizing)
            scores.append(score)

        return sum(scores) / len(scores) if minimizing else max(scores)

    def get_moves(self):
        # generate all possible moves
        # ...

    def make_move(self, move):
        start = (move[0], move[1])
        end = (move[2], move[3])
        self.board[end[0]][end[1]] = self.board[start[0]][start[1]]
        self.board[start[0]][start[1]] = ' '

    def play(self):
        while True:
            if self.turn == 'white':
                best_move = None
                max_score = float('-inf')
                for move in self.get_moves():
                    self.make_move(move)
                    score = self.minimax(3, -float('inf'), float('inf'), False)
                    self.undo_move()
                    if score > max_score:
                        max_score = score
                        best_move = move
                self.make_move(best_move)
            else:
                # AI makes a random move (for simplicity)
                move = random.choice(self.get_moves())
                self.make_move(move)
            self.turn = 'black' if self.turn == 'white' else 'white'
            self.print_board()

    def undo_move(self):
        # undo the last move
        # ...

if __name__ == '__main__':
    game = ChessGame()
    game.play()