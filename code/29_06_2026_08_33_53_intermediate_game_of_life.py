def count_neighbors(board, x, y):
    neighbors = 0
    for i in range(-1, 2):
        for j in range(-1, 2):
            if (i == 0 and j == 0) or i < -1 or j < -1 or i > 0 or j > 0:
                continue
            neighbors += board[(x + i) % len(board)][(y + j) % len(board)]
    return neighbors

def next_generation(board):
    new_board = [[False for _ in range(len(board[0]))] for _ in range(len(board))]
    for x in range(len(board)):
        for y in range(len(board[0])):
            live_neighbors = count_neighbors(board, x, y)
            if board[x][y]:
                new_board[x][y] = (live_neighbors >= 2 and live_neighbors <= 3) or live_neighbors == 3
            else:
                new_board[x][y] = live_neighbors == 3
    return new_board

def game_of_life(board):
    generations = []
    current_generation = board.copy()
    for _ in range(100):  # Run 100 generations
        generations.append(current_generation)
        current_generation = next_generation(current_generation)
    return generations

# Example usage:
if __name__ == '__main__':
    board = [[0, 1, 0],
            [0, 0, 1],
            [1, 1, 1]]
    generations = game_of_life(board)
    for generation in generations:
        print("\n".join([' '.join([str(cell) for cell in row]) for row in generation]))