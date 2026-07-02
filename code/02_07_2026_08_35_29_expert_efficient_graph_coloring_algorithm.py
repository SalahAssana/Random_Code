# Efficient Graph Coloring Algorithm (Expert Level)

import heapq
from collections import deque
from typing import Dict, List, Tuple

class Graph:
    def __init__(self, num_nodes: int):
        self.num_nodes = num_nodes
        self.adj_list: Dict[int, List[Tuple[int, int]]] = {i: [] for i in range(num_nodes)}
        self.color_map: Dict[int, int] = {}

    def add_edge(self, node1: int, node2: int, color: int):
        self.adj_list[node1].append((node2, color))
        self.adj_list[node2].append((node1, color))

    def get_unvisited_neighbors(self, node: int) -> List[int]:
        return [neighbor for neighbor, _ in self.adj_list[node]]

    def is_color_conflict(self, node: int, color: int) -> bool:
        for neighbor, c in self.adj_list[node]:
            if c == color and neighbor != -1:
                return True
        return False

    def dfs(self, node: int) -> None:
        visited = set()
        stack = deque([(node, 0)])
        while stack:
            node, color = stack.pop()
            if node in visited:
                continue
            visited.add(node)
            self.color_map[node] = color
            for neighbor, c in self.adj_list[node]:
                if c == color and neighbor not in visited:
                    return False
            return True

    def is_colorable(self) -> bool:
        colors = [i for i in range(self.num_nodes)]
        pq = [(len(colors), 0)]  # priority queue
        while pq:
            _, k = heapq.heappop(pq)
            if self.is_color_conflict(k, colors[k]):
                return False
            colors[k] = -1  # mark as visited
            for neighbor in self.get_unvisited_neighbors(k):
                if neighbor not in colors or colors[neighbor] == -1:
                    pq.append((len(colors), neighbor))
        return True

    def get_color_map(self) -> Dict[int, int]:
        return self.color_map

# Example usage
if __name__ == '__main__':
    num_nodes = 10
    graph = Graph(num_nodes)
    # Add edges to the graph (e.g., {0: [(1, 0), (2, 0)], 1: [(0, 0), (3, 0)], ...}
    if graph.is_colorable():
        print("Graph is colorable!")
        for node, color in graph.get_color_map().items():
            print(f"Node {node} has color {color}")
    else:
        print("Graph is not colorable.")