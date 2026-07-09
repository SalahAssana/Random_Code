#!/usr/bin/env python3
# coding=utf8

import heapq
import math

class Node:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.parent = None
        self.g = 0
        self.h = 0
        self.f = 0

    def __eq__(self, other):
        return (self.x, self.y) == (other.x, other.y)

class Graph:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.nodes = [[Node(x, y) for y in range(height)] for x in range(width)]
        for x in range(width):
            for y in range(height):
                if (x + y) % 2 == 1:
                    self.nodes[x][y].obstacle = True

    def astar(self, start, end):
        open_list = []
        closed_list = set()
        pq = heapq.heapify([(0, start)])
        while pq:
            _, node = heapq.heappop(pq)
            if node == end:
                return self.reconstruct_path(node)
            closed_list.add(node)
            for dx in [-1, 0, 1]:
                for dy in [-1, 0, 1]:
                    if abs(dx) + abs(dy) != 1:
                        continue
                    x = node.x + dx
                    y = node.y + dy
                    if (x < 0 or y < 0 or x >= self.width or y >= self.height or 
                            self.nodes[x][y].obstacle or (x, y) in closed_list):
                        continue
                    new_node = Node(x, y)
                    new_node.parent = node
                    new_node.g = node.g + 1
                    new_node.h = abs(x - end.x) + abs(y - end.y)
                    new_node.f = new_node.g + new_node.h
                    heapq.heappush(open_list, (new_node.f, new_node))
        return None

    def reconstruct_path(self, node):
        path = [node]
        while node.parent:
            node = node.parent
            path.append(node)
        return list(reversed(path))

if __name__ == '__main__':
    maze = Graph(10, 10)
    start = maze.nodes[1][1]
    end = maze.nodes[8][8]
    path = maze.astar(start, end)
    if path:
        for node in path:
            print(f"{node.x}, {node.y}")