import numpy as np
from random import randint, uniform
import matplotlib.pyplot as plt

class Player:
    def __init__(self):
        self.position = [0, 0]
        self.score = 0

    def move(self):
        direction = randint(1, 4)
        if direction == 1:  # up
            self.position[1] += 1
        elif direction == 2:  # down
            self.position[1] -= 1
        elif direction == 3:  # left
            self.position[0] -= 1
        else:  # right
            self.position[0] += 1

    def check_score(self):
        if self.position[0] > 10 and self.position[1] > 10:
            return True
        elif self.position[0] < -10 or self.position[1] < -10:
            return False
        else:
            return None

class Game:
    def __init__(self, num_players=2):
        self.players = [Player() for _ in range(num_players)]

    def run(self):
        while True:
            for player in self.players:
                player.move()
                score_check = player.check_score()
                if score_check is not None:
                    return score_check

    def plot_positions(self, positions):
        plt.scatter([p[0] for p in positions], [p[1] for p in positions])
        plt.show()

def main():
    game = Game()
    result = game.run()
    print(f"Game Over: {'You Win' if result else 'You Lose'}")
    positions = [[player.position[0], player.position[1]] for player in game.players]
    game.plot_positions(positions)

if __name__ == '__main__':
    main()