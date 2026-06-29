import heapq
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import networkx as nx
import numpy as np

class Graph:
    def __init__(self):
        self.adj_list = {}

    def add_edge(self, node1, node2, weight=1):
        if node1 not in self.adj_list:
            self.adj_list[node1] = []
        if node2 not in self.adj_list:
            self.adj_list[node2] = []
        self.adj_list[node1].append((node2, weight))
        self.adj_list[node2].append((node1, weight))

    def dijkstra(self, start):
        queue = [(0, start)]
        distances = {node: float('inf') for node in self.adj_list}
        distances[start] = 0
        previous_nodes = {start: None}

        while queue:
            (dist, current_node) = heapq.heappop(queue)

            if dist > distances[current_node]:
                continue

            for neighbor, weight in self.adj_list.get(current_node, []):
                old_dist = distances[neighbor]
                new_dist = distances[current_node] + weight
                if new_dist < old_dist:
                    distances[neighbor] = new_dist
                    previous_nodes[neighbor] = current_node
                    heapq.heappush(queue, (new_dist, neighbor))

        return {node: path for node, path in previous_nodes.items()}

class Visualizer:
    def __init__(self):
        self.graph = None

    def visualize(self, graph):
        if not graph:
            return

        self.graph = graph
        G = nx.DiGraph()
        for node1, neighbors in graph.adj_list.items():
            for node2, _ in neighbors:
                G.add_edge(node1, node2)

        pos = nx.spring_layout(G)
        plt.figure(figsize=(10, 10))
        nx.draw_networkx(G, pos, with_labels=True, font_size=12)

        for edge in list(G.edges):
            if self.graph.adj_list[edge[0]][list(map(lambda x: x[0], self.graph.adj_list[edge[0]]))].index((edge[1], 1)):
                G.remove_edge(*edge)
        nx.draw_networkx(G, pos, with_labels=True, font_size=12)

        plt.show()

def main():
    graph = Graph()
    graph.add_edge('A', 'B', weight=3)
    graph.add_edge('A', 'C', weight=2)
    graph.add_edge('B', 'C', weight=1)
    graph.add_edge('D', 'E', weight=4)
    graph.add_edge('D', 'F', weight=5)

    shortest_paths = graph.dijkstra('A')
    print("Shortest paths:")
    for node, path in shortest_paths.items():
        if node != 'A':
            print(f"{node}: {path}")

    visualizer = Visualizer()
    visualizer.visualize(graph)

if __name__ == '__main__':
    main()