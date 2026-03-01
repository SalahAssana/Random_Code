import heapq
import sys

class Graph:
    def __init__(self):
        self.adj_list = {}

    def add_edge(self, node1, node2, weight):
        if node1 not in self.adj_list:
            self.adj_list[node1] = []
        if node2 not in self.adj_list:
            self.adj_list[node2] = []

        self.adj_list[node1].append((node2, weight))
        self.adj_list[node2].append((node1, weight))

    def dijkstra(self, start_node):
        queue = [(0, start_node)]
        distances = {node: sys.maxsize for node in self.adj_list}
        distances[start_node] = 0
        previous_nodes = {start_node: None}

        while queue:
            current_distance, current_node = heapq.heappop(queue)

            if current_distance > distances[current_node]:
                continue

            for neighbor, weight in self.adj_list[current_node]:
                distance = current_distance + weight
                if distance < distances[neighbor]:
                    distances[neighbor] = distance
                    previous_nodes[neighbor] = current_node
                    heapq.heappush(queue, (distance, neighbor))

        return distances, previous_nodes

# Example usage:
graph = Graph()
graph.add_edge('A', 'B', 4)
graph.add_edge('A', 'C', 2)
graph.add_edge('B', 'D', 3)
graph.add_edge('C', 'D', 1)

start_node = 'A'
distances, previous_nodes = graph.dijkstra(start_node)

print(f"Shortest distances from {start_node}:")
for node, distance in distances.items():
    print(f"{node}: {distance}")

print("\nPrevious nodes in shortest path:")
for node, prev_node in previous_nodes.items():
    if prev_node is None:
        print(f"{node} -> None (root node)")
    else:
        print(f"{node} -> {prev_node}")