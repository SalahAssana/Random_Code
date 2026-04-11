import heapq
import time
from collections import deque

class Node:
    def __init__(self, id):
        self.id = id
        self.distance = float('inf')
        self.parent = None

class Graph:
    def __init__(self):
        self.nodes = {}
        self.edges = []

    def add_node(self, node_id):
        self.nodes[node_id] = Node(node_id)

    def add_edge(self, start, end, weight):
        self.edges.append((start, end, weight))

    def dijkstra(self, start, goal):
        queue = [(0, start)]
        distances = {node.id: float('inf') for node in self.nodes.values()}
        distances[start] = 0
        parent_nodes = {}

        while queue:
            (dist, current) = heapq.heappop(queue)

            if dist > distances[current]:
                continue

            for edge in self.edges:
                start_node_id, end_node_id, weight = edge
                if start_node_id == current and end_node_id not in parent_nodes:
                    new_dist = distances[start_node_id] + weight
                    if new_dist < distances[end_node_id]:
                        distances[end_node_id] = new_dist
                        parent_nodes[end_node_id] = current
                        heapq.heappush(queue, (new_dist, end_node_id))

        return distances[goal]

    def a_star(self, start, goal):
        queue = [(0, start)]
        distances = {node.id: float('inf') for node in self.nodes.values()}
        distances[start] = 0
        parent_nodes = {}

        while queue:
            (dist, current) = heapq.heappop(queue)

            if dist > distances[current]:
                continue

            for edge in self.edges:
                start_node_id, end_node_id, weight = edge
                if start_node_id == current and end_node_id not in parent_nodes:
                    new_dist = distances[start_node_id] + weight
                    heuristic = abs(int(end_node_id) - int(goal))  # Manhattan distance as heuristic
                    if new_dist < distances[end_node_id]:
                        distances[end_node_id] = new_dist
                        parent_nodes[end_node_id] = current
                        heapq.heappush(queue, (new_dist + heuristic, end_node_id))

        return distances[goal]

    def bfs(self, start, goal):
        queue = deque([(start, [start])])
        visited = set()

        while queue:
            node, path = queue.popleft()
            if node not in visited:
                visited.add(node)
                if node == goal:
                    return path

                for edge in self.edges:
                    start_node_id, end_node_id, _ = edge
                    if start_node_id == node and end_node_id not in visited:
                        queue.append((end_node_id, [node] + path))

        return None

def main():
    graph = Graph()
    graph.add_node(0)
    graph.add_node(1)
    graph.add_node(2)
    graph.add_node(3)
    graph.add_edge(0, 1, 4)
    graph.add_edge(0, 2, 8)
    graph.add_edge(1, 2, 7)
    graph.add_edge(1, 3, 9)
    graph.add_edge(2, 3, 6)

    start_time = time.time()
    dijkstra_distance = graph.dijkstra(0, 3)
    end_time = time.time()
    print(f"Dijkstra's algorithm took {end_time - start_time} seconds")
    print(f"The shortest distance from node 0 to node 3 using Dijkstra's algorithm is {dijkstra_distance}")

    start_time = time.time()
    a_star_distance = graph.a_star(0, 3)
    end_time = time.time()
    print(f"A* search algorithm took {end_time - start_time} seconds")
    print(f"The shortest distance from node 0 to node 3 using A* search algorithm is {a_star_distance}")

    start_time = time.time()
    bfs_path = graph.bfs(0, 3)
    end_time = time.time()
    print(f"Breadth-First Search algorithm took {end_time - start_time} seconds")
    if bfs_path:
        print(f"The shortest path from node 0 to node 3 using Breadth-First Search algorithm is {bfs_path}")
    else:
        print("No path found")

if __name__ == '__main__':
    main()