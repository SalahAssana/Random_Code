import pygame
import random
import time

# Constants
WIDTH, HEIGHT = 800, 600
ARRAY_SIZE = 20
ALGORITHMS = ['Bubble Sort', 'Selection Sort', 'Insertion Sort']

class Array:
    def __init__(self):
        self.values = [random.randint(1, 100) for _ in range(ARRAY_SIZE)]

    def swap(self, i, j):
        self.values[i], self.values[j] = self.values[j], self.values[i]

    def visualize(self):
        return [colorize(val) for val in self.values]

def colorize(val):
    if val < 50:
        return (255, 0, 0)
    elif val < 75:
        return (0, 255, 0)
    else:
        return (0, 0, 255)

class Algorithm:
    def __init__(self, array):
        self.array = array

    def visualize(self):
        # Main loop
        for i in range(len(self.array.values)):
            pygame.event.get()
            screen.fill((255, 255, 255))
            for j, val in enumerate(self.array.visualize()):
                pygame.draw.rect(screen, colorize(val), (j * WIDTH // len(self.array.values), HEIGHT - self.array.values[i], WIDTH // len(self.array.values), self.array.values[i]))
            pygame.display.update()
            time.sleep(0.01)

        # Reset array
        for i in range(len(self.array.values)):
            self.array.swap(i, random.randint(0, len(self.array.values) - 1))

def main():
    global screen

    pygame.init()
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption('Sorting Visualizer')

    array = Array()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    algorithm = Algorithm(array)
                    algorithm.visualize()

if __name__ == '__main__':
    main()