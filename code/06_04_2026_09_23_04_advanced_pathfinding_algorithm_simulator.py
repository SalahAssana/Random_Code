import heapq
import math

class Node:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.parent = None
        self.distance = float('inf')
        self.heuristic = 0

class Maze:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.nodes = [[Node(x, y) for y in range(height)] for x in range(width)]

    def set_wall(self, x, y):
        if x < 0 or x >= self.width or y < 0 or y >= self.height:
            return False
        self.nodes[x][y].wall = True
        return True

class Pathfinder:
    def __init__(self, maze):
        self.maze = maze

    def dijkstra(self, start_x, start_y, end_x, end_y):
        start_node = self.maze.nodes[start_x][start_y]
        start_node.distance = 0
        queue = [(0, start_node)]
        while queue:
            (dist, node) = heapq.heappop(queue)
            if node.x == end_x and node.y == end_y:
                break
            for dx in range(-1, 2):
                for dy in range(-1, 2):
                    if abs(dx) + abs(dy) != 1 or node.wall:
                        continue
                    neighbor = self.maze.nodes[node.x+dx][node.y+dy]
                    new_dist = dist + 1
                    if new_dist < neighbor.distance:
                        neighbor.parent = node
                        neighbor.distance = new_dist
                        heapq.heappush(queue, (new_dist, neighbor))
        return self._reconstruct_path(start_node)

    def astar(self, start_x, start_y, end_x, end_y):
        start_node = self.maze.nodes[start_x][start_y]
        start_node.distance = 0
        queue = [(0, start_node)]
        while queue:
            (dist, node) = heapq.heappop(queue)
            if node.x == end_x and node.y == end_y:
                break
            for dx in range(-1, 2):
                for dy in range(-1, 2):
                    if abs(dx) + abs(dy) != 1 or node.wall:
                        continue
                    neighbor = self.maze.nodes[node.x+dx][node.y+dy]
                    new_dist = dist + 1
                    heuristic = math.hypot(neighbor.x-end_x, neighbor.y-end_y)
                    if new_dist < neighbor.distance:
                        neighbor.parent = node
                        neighbor.distance = new_dist
                        heapq.heappush(queue, (new_dist + heuristic, neighbor))
        return self._reconstruct_path(start_node)

    def _reconstruct_path(self, end_node):
        path = []
        while end_node:
            path.append((end_node.x, end_node.y))
            end_node = end_node.parent
        return list(reversed(path))

if __name__ == '__main__':
    maze = Maze(10, 10)
    maze.set_wall(1, 1)
    maze.set_wall(2, 1)
    maze.set_wall(3, 1)
    maze.set_wall(9, 9)
    pathfinder = Pathfinder(maze)
    start_x, start_y = 0, 0
    end_x, end_y = 9, 9
    dijkstra_path = pathfinder.dijkstra(start_x, start_y, end_x, end_y)
    print("Dijkstra's shortest path:", dijkstra_path)
    astar_path = pathfinder.astar(start_x, start_y, end_x, end_y)
    print("A* algorithm's shortest path:", astar_path)