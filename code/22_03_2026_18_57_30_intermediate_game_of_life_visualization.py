import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Set the size of the grid
SIZE = 100

class GameOfLife:
    def __init__(self):
        self.grid = np.random.randint(0, 2, (SIZE, SIZE))

    def next_generation(self):
        new_grid = np.zeros((SIZE, SIZE))
        for i in range(SIZE):
            for j in range(SIZE):
                # Count the number of alive neighbors
                count = 0
                for x in range(max(0, i-1), min(SIZE, i+2)):
                    for y in range(max(0, j-1), min(SIZE, j+2)):
                        if (x, y) != (i, j) and self.grid[x][y] == 1:
                            count += 1
                # Apply the rules of the Game of Life
                if self.grid[i][j] == 1 and (count < 2 or count > 3):
                    new_grid[i][j] = 0
                elif self.grid[i][j] == 0 and count == 3:
                    new_grid[i][j] = 1
                else:
                    new_grid[i][j] = self.grid[i][j]
        return new_grid

    def visualize(self):
        fig, ax = plt.subplots()
        im = ax.imshow(self.grid, cmap='Greys', interpolation='nearest')
        def animate(i):
            self.grid = self.next_generation()
            im.set_array(self.grid)
            return [im]
        anim = animation.FuncAnimation(fig, animate, frames=200, interval=100, blit=True)
        plt.show()

if __name__ == '__main__':
    game = GameOfLife()
    game.visualize()