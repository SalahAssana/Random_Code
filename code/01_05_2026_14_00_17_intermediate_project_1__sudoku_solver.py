# Sudoku Solver in Python
import copy

def is_valid(board, row, col, num):
    # Check if the number already exists in the row
    for x in range(9):
        if board[row][x] == num:
            return False
    
    # Check if the number already exists in the column
    for x in range(9):
        if board[x][col] == num:
            return False
    
    # Check if the number already exists in the 3x3 box
    start_row = row - row % 3
    start_col = col - col % 3
    for i in range(3):
        for j in range(3):
            if board[i + start_row][j + start_col] == num:
                return False
    return True

def solve_sudoku(board):
    for x in range(9):
        for y in range(9):
            if board[x][y] == 0:
                for i in range(1, 10):
                    if is_valid(board, x, y, i):
                        board[x][y] = i
                        if solve_sudoku(board):
                            return True
                        else:
                            board[x][y] = 0
                return False
    return True

def print_board(board):
    for i in range(9):
        if i % 3 == 0 and i != 0:
            print("- - - - - - - - - - - -")
        for j in range(9):
            if j % 3 == 0 and j != 0:
                print(" | ", end="")
            if j == 8:
                print(board[i][j])
            else:
                print(str(board[i][j]) + " ", end="")

# Test the Sudoku solver
board = [
    [5,1,7,6,0,0,0,3,4],
    [2,8,9,0,0,4,0,0,0],
    [3,4,6,2,0,5,0,9,8],
    [1,6,0,3,4,0,0,0,2],
    [8,5,0,0,1,3,0,4,0],
    [4,2,0,9,7,6,0,0,0],
    [3,0,0,0,2,1,0,8,9],
    [9,7,1,5,3,0,0,2,6],
    [6,3,4,8,5,7,0,1,0]
]

if solve_sudoku(board):
    print("Solved Sudoku:")
    print_board(board)
else:
    print("No solution exists for this puzzle.")