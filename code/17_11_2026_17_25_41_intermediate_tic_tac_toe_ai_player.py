# Tic-Tac-Toe AI Player
import random

class TicTacToe:
    def __init__(self):
        self.board = [[' ' for _ in range(3)] for _ in range(3)]
        self.player_turn = True

    def print_board(self):
        print(f"{self.board[0][0]} | {self.board[0][1]} | {self.board[0][2]}")
        print("---+---+---")
        print(f"{self.board[1][0]} | {self.board[1][1]} | {self.board[1][2]}")
        print("---+---+---")
        print(f"{self.board[2][0]} | {self.board[2][1]} | {self.board[2][2]}")

    def is_valid_move(self, row, col):
        return 0 <= row < 3 and 0 <= col < 3 and self.board[row][col] == ' '

    def make_move(self, row, col):
        if self.is_valid_move(row, col):
            self.board[row][col] = 'X' if self.player_turn else 'O'
            self.player_turn = not self.player_turn
        else:
            raise ValueError("Invalid move")

    def has_won(self):
        for i in range(3):
            if self.board[i][0] == self.board[i][1] == self.board[i][2]:
                return True
            if self.board[0][i] == self.board[1][i] == self.board[2][i]:
                return True
        if self.board[0][0] == self.board[1][1] == self.board[2][2]:
            return True
        if self.board[0][2] == self.board[1][1] == self.board[2][0]:
            return True
        return False

    def is_draw(self):
        for row in self.board:
            for cell in row:
                if cell == ' ':
                    return False
        return True

    def minimax(self, depth, alpha, beta, is_maximizing_player):
        winner = self.has_won()
        if winner:
            if is_maximizing_player:
                return -1 if winner else 1
            else:
                return 1 if winner else -1
        elif self.is_draw():
            return 0

        if is_maximizing_player:
            value = float('-inf')
            for i in range(3):
                for j in range(3):
                    if self.board[i][j] == ' ':
                        self.make_move(i, j)
                        value = max(value, self.minimax(depth + 1, alpha, beta, False))
                        self.undo_move(i, j)
                        alpha = max(alpha, value)
                        if beta <= alpha:
                            break
            return value

        else:
            value = float('inf')
            for i in range(3):
                for j in range(3):
                    if self.board[i][j] == ' ':
                        self.make_move(i, j)
                        value = min(value, self.minimax(depth + 1, alpha, beta, True))
                        self.undo_move(i, j)
                        beta = min(beta, value)
                        if beta <= alpha:
                            break
            return value

    def undo_move(self, row, col):
        self.board[row][col] = ' '

    def play(self):
        while not self.has_won() and not self.is_draw():
            print("Player turn:")
            self.print_board()
            try:
                row = int(input("Enter row (0-2): "))
                col = int(input("Enter column (0-2): "))
                self.make_move(row, col)
                if self.has_won():
                    self.print_board()
                    print(f"Player {1 if self.player_turn else 2} wins!")
                    break
            except ValueError:
                print("Invalid input. Try again.")
        if self.is_draw():
            self.print_board()
            print("It's a draw!")

    def ai_move(self):
        best_value = float('-inf')
        best_move = None
        for i in range(3):
            for j in range(3):
                if self.board[i][j] == ' ':
                    self.make_move(i, j)
                    value = self.minimax(0, -float('inf'), float('inf'), False)
                    self.undo_move(i, j)
                    if value > best_value:
                        best_value = value
                        best_move = (i, j)

        self.make_move(best_move[0], best_move[1])
        print("AI's turn:")
        self.print_board()

    def play_against_ai(self):
        while not self.has_won() and not self.is_draw():
            self.ai_move()
            if self.has_won():
                self.print_board()
                print(f"AI wins!")
                break
        if self.is_draw():
            self.print_board()
            print("It's a draw!")

if __name__ == '__main__':
    game = TicTacToe()
    while True:
        print("\n1. Play against human\n2. Play against AI")
        choice = input("Enter your choice (1/2): ")
        if choice == '1':
            game.play()
        elif choice == '2':
            game.play_against_ai()
        else:
            print("Invalid input. Try again.")