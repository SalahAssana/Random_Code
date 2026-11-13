# Tic-Tac-Toe Game
# Complexity Level: BEGINNER

board = [[' ' for _ in range(3)] for _ in range(3)]
player_turn = 'X'

def print_board():
    print(" " + board[0][0] + " | " + board[0][1] + " | " + board[0][2])
    print("---+---+---")
    print(" " + board[1][0] + " | " + board[1][1] + " | " + board[1][2])
    print("---+---+---")
    print(" " + board[2][0] + " | " + board[2][1] + " | " + board[2][2])

def check_win():
    for i in range(3):
        if board[i][0] == board[i][1] == board[i][2] != ' ':
            return board[i][0]
        if board[0][i] == board[1][i] == board[2][i] != ' ':
            return board[0][i]
    if board[0][0] == board[1][1] == board[2][2] != ' ':
        return board[0][0]
    if board[0][2] == board[1][1] == board[2][0] != ' ':
        return board[0][2]
    return None

def ai_move():
    import random
    for i in range(3):
        for j in range(3):
            if board[i][j] == ' ':
                board[i][j] = 'O'
                result = check_win()
                if result:
                    return
                board[i][j] = ' '
    # If no win, choose a random spot
    import random
    while True:
        i = random.randint(0, 2)
        j = random.randint(0, 2)
        if board[i][j] == ' ':
            board[i][j] = 'O'
            return

if __name__ == '__main__':
    print("Tic-Tac-Toe Game")
    while True:
        print_board()
        if player_turn == 'X':
            row = int(input("Enter row (0-2): "))
            col = int(input("Enter column (0-2): "))
            if board[row][col] != ' ':
                print("Invalid move, try again.")
                continue
            board[row][col] = 'X'
        else:
            ai_move()
        result = check_win()
        if result:
            print_board()
            print("Player", player_turn, "wins!")
            break
        if all(cell != ' ' for row in board for cell in row):
            print_board()
            print("It's a draw!")
            break
        player_turn = 'O' if player_turn == 'X' else 'X'