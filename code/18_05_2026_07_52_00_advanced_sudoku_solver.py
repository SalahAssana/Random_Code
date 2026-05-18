# Sudoku Solver in Python

import copy

def is_valid(board, row, col, num):
    # Check the number in the row
    for x in range(9):
        if board[row][x] == num:
            return False
    
    # Check the number in the column
    for x in range(9):
        if board[x][col] == num:
            return False
    
    # Check the box
    start_row = row - row % 3
    start_col = col - col % 3
    for i in range(3):
        for j in range(3):
            if board[i + start_row][j + start_col] == num:
                return False
    return True

def solve_sudoku(board):
    for i in range(9):
        for j in range(9):
            if board[i][j] == 0:
                for num in range(1, 10):
                    if is_valid(board, i, j, num):
                        board[i][j] = num
                        if solve_sudoku(board):
                            return True
                        else:
                            board[i][j] = 0
                return False
    return True

def print_board(board):
    for i in range(9):
        if i % 3 == 0 and i != 0:
            print("- - - - - - - - - - -")
        for j in range(9):
            if j % 3 == 0 and j != 0:
                print(" | ", end="")
            if j == 8:
                print(board[i][j])
            else:
                print(str(board[i][j]) + " ", end="")

if __name__ == '__main__':
    board = [[5,1,7,6,0,0,0,3,4],
             [2,8,9,0,0,4,0,0,0],
             [3,4,6,2,0,5,0,0,0],
             [6,0,2,0,0,3,0,0,0],
             [0,3,1,0,8,6,4,0,0],
             [1,6,4,3,0,2,0,0,0],
             [8,5,0,0,4,1,3,0,0],
             [4,2,0,0,5,3,0,9,0],
             [7,6,3,4,0,0,5,2,0]]

    if solve_sudoku(board):
        print_board(board)
    else:
        print("No solution exists")