def initialize_grid(rows, cols):
    import random
    grid = [[random.choice([0,1]) for _ in range(cols)] for _ in range(rows)]
    return grid

def count_neighbors(grid, row, col):
    neighbors = 0
    for r in range(max(0, row-1), min(len(grid), row+2)):
        for c in range(max(0, col-1), min(len(grid[0]), col+2)):
            if (r != row or c != col) and grid[r][c] == 1:
                neighbors += 1
    return neighbors

def next_generation(grid):
    rows = len(grid)
    cols = len(grid[0])
    new_grid = [[0 for _ in range(cols)] for _ in range(rows)]
    for row in range(rows):
        for col in range(cols):
            live_neighbors = count_neighbors(grid, row, col)
            if grid[row][col] == 1:
                if live_neighbors < 2 or live_neighbors > 3:
                    new_grid[row][col] = 0
                else:
                    new_grid[row][col] = 1
            elif live_neighbors == 3:
                new_grid[row][col] = 1
    return new_grid

def game_of_life(rows, cols, generations):
    grid = initialize_grid(rows, cols)
    for _ in range(generations):
        print("Generation: ", _+1)
        for row in range(len(grid)):
            for col in range(len(grid[0])):
                if grid[row][col] == 1:
                    print("#", end=" ")
                else:
                    print(" ", end=" ")
            print()
        grid = next_generation(grid)

if __name__ == '__main__':
    rows = int(input("Enter the number of rows: "))
    cols = int(input("Enter the number of columns: "))
    generations = int(input("Enter the number of generations: "))
    game_of_life(rows, cols, generations)