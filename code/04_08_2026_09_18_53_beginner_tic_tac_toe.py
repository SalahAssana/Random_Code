# Tic Tac Toe game for beginners

import random

board = [' ' for _ in range(9)]

def print_board():
    row1 = '| {} | {} | {} |'.format(board[0], board[1], board[2])
    row2 = '| {} | {} | {} |'.format(board[3], board[4], board[5])
    row3 = '| {} | {} | {} |'.format(board[6], board[7], board[8])

    print()
    print(row1)
    print(row2)
    print(row3)
    print()

def player_move(icon):
    if icon == 'X':
        number = 1
    elif icon == 'O':
        number = 2

    while True:
        print("Your turn player {}".format(number))
        move = input("Enter your move (1-9): ").lower()
        try:
            move = int(move)
        except ValueError:
            print("Invalid input. Please enter a number within the range.")
            continue
        if move < 1 or move > 9:
            print("Invalid input. Please enter a number within the range.")
            continue
        if board[move - 1] == ' ':
            board[move - 1] = icon
            return
        else:
            print("That space is taken. Try again.")

def computer_move(icon):
    if icon == 'X':
        other_icon = 'O'
    elif icon == 'O':
        other_icon = 'X'

    while True:
        move = random.randint(1, 9)
        if board[move - 1] == ' ':
            board[move - 1] = icon
            return

def check_winner():
    winning_combos = [(0, 1, 2), (3, 4, 5), (6, 7, 8),
                      (0, 3, 6), (1, 4, 7), (2, 5, 8),
                      (0, 4, 8), (2, 4, 6)]
    for combo in winning_combos:
        if board[combo[0]] == board[combo[1]] == board[combo[2]] != ' ':
            return board[combo[0]]
    if ' ' not in board:
        return 'Tie'
    return False

if __name__ == '__main__':
    print("Welcome to Tic Tac Toe!")
    icon = 'X' if random.randint(0, 1) else 'O'
    print("You're playing as {}".format(icon))

    while True:
        print_board()
        player_move(icon)
        winner = check_winner()
        if winner:
            print_board()
            if winner == 'Tie':
                print("It's a tie!")
            else:
                print("Player {} wins! Congratulations!".format('you' if winner == icon else 'the computer'))
            break
        icon = 'O' if icon == 'X' else 'X'
        computer_move(icon)
        winner = check_winner()
        if winner:
            print_board()
            if winner == 'Tie':
                print("It's a tie!")
            else:
                print("Player {} wins! Congratulations!".format('you' if winner == icon else 'the computer'))
            break