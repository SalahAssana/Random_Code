import heapq
from collections import defaultdict

class Node:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.g = float('inf')  # cost from start node
        self.h = 0  # heuristic value
        self.f = 0  # total cost (g + h)
        self.parent = None

class Grid:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.nodes = [[Node(x, y) for y in range(height)] for x in range(width)]
        self.walls = defaultdict(list)

    def set_wall(self, x1, y1, x2, y2):
        if 0 <= x1 < self.width and 0 <= y1 < self.height and 0 <= x2 < self.width and 0 <= y2 < self.height:
            self.walls[(x1, y1)].append((x2, y2))
            self.walls[(x2, y2)].append((x1, y1))

    def a_star_search(self, start, end):
        open_list = []
        heapq.heappush(open_list, (0, start))
        came_from = {}
        g_score = {node: float('inf') for row in self.nodes for node in row}
        g_score[start] = 0

        while open_list:
            _, current_node = heapq.heappop(open_list)
            if current_node == end:
                break
            for neighbor in self.get_neighbors(current_node):
                tentative_g_score = g_score[current_node] + 1
                if tentative_g_score < g_score[neighbor]:
                    came_from[neighbor] = current_node
                    g_score[neighbor] = tentative_g_score
                    heapq.heappush(open_list, (tentative_g_score + self.heuristic(neighbor, end), neighbor))

        path = []
        while current_node:
            path.append(current_node)
            current_node = came_from[current_node]
        return list(reversed(path))

    def get_neighbors(self, node):
        neighbors = []
        for x in [-1, 0, 1]:
            for y in [-1, 0, 1]:
                if abs(x) + abs(y) == 1 and 0 <= node.x + x < self.width and 0 <= node.y + y < self.height:
                    neighbor = self.nodes[node.x + x][node.y + y]
                    if (node.x, node.y) not in self.walls and (neighbor.x, neighbor.y) not in self.walls:
                        neighbors.append(neighbor)
        return neighbors

    def heuristic(self, node1, node2):
        dx = abs(node1.x - node2.x)
        dy = abs(node1.y - node2.y)
        return dx + dy

if __name__ == '__main__':
    grid = Grid(10, 10)
    grid.set_wall(0, 0, 9, 9)
    start = grid.nodes[5][5]
    end = grid.nodes[0][0]
    path = grid.a_star_search(start, end)
    print(path)