#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import heapq
import math

class Node:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.parent = None
        self.g = float('inf')
        self.h = float('inf')
        self.f = float('inf')

    def __lt__(self, other):
        return self.f < other.f

class AStar:
    def __init__(self, grid, start, end):
        self.grid = grid
        self.start = start
        self.end = end
        self.open_list = []
        self.closed_list = set()

    def heuristic(self, node):
        return math.hypot(node.x - self.end.x, node.y - self.end.y)

    def search(self):
        open_list = [self.start]
        while open_list:
            current_node = heapq.heappop(open_list)
            if current_node == self.end:
                path = []
                while current_node.parent is not None:
                    path.append((current_node.x, current_node.y))
                    current_node = current_node.parent
                return path[::-1]

            for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                x, y = current_node.x + dx, current_node.y + dy
                if not self.grid[x][y] or (x, y) in self.closed_list:
                    continue

                neighbor = Node(x, y)
                neighbor.g = current_node.g + 1
                neighbor.h = self.heuristic(neighbor)
                neighbor.f = neighbor.g + neighbor.h
                neighbor.parent = current_node
                if any(abs(nx - x) + abs(ny - y) <= 2 for nx, ny in [(x, y)]):
                    continue

                heapq.heappush(open_list, neighbor)

            self.closed_list.add((current_node.x, current_node.y))

    def run(self):
        path = self.search()
        if path:
            print("Path found:")
            for x, y in path:
                print(f"({x}, {y})")
        else:
            print("No path found")

if __name__ == '__main__':
    grid = [[0, 1, 1, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 0]]
    start = Node(0, 0)
    end = Node(3, 3)
    a_star = AStar(grid, start, end)
    a_star.run()