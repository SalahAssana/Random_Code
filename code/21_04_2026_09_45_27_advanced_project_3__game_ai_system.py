import numpy as np
from scipy.spatial import distance
import random

class Player:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Enemy:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class GameAI:
    def __init__(self, player, enemies):
        self.player = player
        self.enemies = enemies
        self.pathfinding_distance_threshold = 5.0
        self.attack_range = 2.0

    def update(self):
        for enemy in self.enemies:
            if distance.euclidean((self.player.x, self.player.y), (enemy.x, enemy.y)) < self.pathfinding_distance_threshold:
                path = self.find_path(self.player, enemy)
                if path:
                    self.move_towards_point(self.player, path[0])
            elif np.linalg.norm(np.array([self.player.x - enemy.x, self.player.y - enemy.y])) <= self.attack_range:
                self.attack(self.player, enemy)

    def find_path(self, start, end):
        queue = [(start.x, start.y)]
        visited = {(start.x, start.y)}
        parent = {}
        while queue:
            x, y = queue.pop(0)
            if (x, y) == (end.x, end.y):
                path = []
                while (x, y) != (start.x, start.y):
                    path.append((x, y))
                    x, y = parent.get((x, y), None)
                return [(start.x, start.y)] + list(reversed(path))
            for dx in [-1, 0, 1]:
                for dy in [-1, 0, 1]:
                    nx, ny = x + dx, y + dy
                    if (nx, ny) not in visited and -5 <= nx <= 5 and -5 <= ny <= 5:
                        queue.append((nx, ny))
                        visited.add((nx, ny))
                        parent[(nx, ny)] = (x, y)
        return None

    def move_towards_point(self, player, point):
        dx = point[0] - player.x
        dy = point[1] - player.y
        if np.linalg.norm([dx, dy]) > 1:
            self.move(player, min(max(1, dx), -1), min(max(1, dy), -1))

    def move(self, player, dx, dy):
        self.player.x += dx
        self.player.y += dy

    def attack(self, player, enemy):
        print(f"Player attacks {enemy}")

if __name__ == '__main__':
    player = Player(0, 0)
    enemies = [Enemy(-1, -1), Enemy(2, 2)]
    game_ai = GameAI(player, enemies)
    for _ in range(100):
        game_ai.update()