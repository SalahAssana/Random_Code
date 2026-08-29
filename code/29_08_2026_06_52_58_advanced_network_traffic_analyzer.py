import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict
from heapq import nlargest

class Node:
    def __init__(self, name):
        self.name = name
        self.incoming_edges = []
        self.outgoing_edges = []

class Edge:
    def __init__(self, from_node, to_node, weight):
        self.from_node = from_node
        self.to_node = to_node
        self.weight = weight

class TrafficAnalyzer:
    def __init__(self):
        self.graph = defaultdict(list)

    def add_edge(self, from_node_name, to_node_name, weight):
        from_node = Node(from_node_name)
        to_node = Node(to_node_name)
        edge = Edge(from_node, to_node, weight)
        self.graph[from_node].append(edge)
        self.graph[to_node].append((edge.from_node, edge.to_node, edge.weight))

    def find_shortest_path(self, start_node, end_node):
        queue = [(0, start_node)]
        distances = {node: float('inf') for node in self.graph}
        previous_nodes = {node: None for node in self.graph}

        while queue:
            (dist, current_node) = heapq.heappop(queue)

            if dist > distances[current_node]:
                continue

            for neighbor, edge_weight in self.graph[current_node]:
                old_dist = distances[neighbor]
                new_dist = dist + edge_weight
                if new_dist < old_dist:
                    distances[neighbor] = new_dist
                    previous_nodes[neighbor] = current_node
                    heapq.heappush(queue, (new_dist, neighbor))

        path = []
        current_node = end_node
        while current_node is not None:
            path.append(current_node)
            current_node = previous_nodes[current_node]
        return list(reversed(path))

    def analyze_traffic(self):
        nodes = set()
        for node in self.graph:
            nodes.add(node.name)

        edge_weights = {}
        for node in self.graph:
            for edge in self.graph[node]:
                from_node, to_node, weight = edge
                if (to_node, weight) not in edge_weights:
                    edge_weights[(to_node, weight)] = 0
                edge_weights[(to_node, weight)] += 1

        top_heavy_edges = nlargest(10, edge_weights.items(), key=lambda x: x[1])

        print("Shortest path from", start_node, "to", end_node, ": ", self.find_shortest_path(start_node, end_node))
        print("Top 10 heavy edges:", top_heavy_edges)

    def visualize(self):
        plt.figure(figsize=(8, 8))
        pos = nx.spring_layout(nx.from_dict_of_dicts({n.name: {'pos': [0.5, i]} for n in self.graph}, pos=nx.spring_layout.pos)
        nx.draw_networkx(self.graph, pos, with_labels=True)

if __name__ == '__main__':
    start_node = 'A'
    end_node = 'E'

    traffic_analyzer = TrafficAnalyzer()

    edges = [
        (start_node, 'B', 2),
        ('B', 'C', 3),
        ('C', 'D', 1),
        ('D', 'E', 4),
        ('B', 'E', 5)
    ]

    for edge in edges:
        traffic_analyzer.add_edge(*edge)

    traffic_analyzer.analyze_traffic()
    traffic_analyzer.visualize()