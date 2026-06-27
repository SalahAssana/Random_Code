import heapq
from collections import defaultdict

class Node:
    def __init__(self, name):
        self.name = name
        self.distance = float('inf')
        self.previous = None

class Graph:
    def __init__(self):
        self.nodes = {}
        self.edges = defaultdict(list)

    def add_node(self, node):
        self.nodes[node.name] = Node(node.name)

    def add_edge(self, from_node, to_node, distance):
        self.edges[from_node].append((to_node, distance))
        self.edges[to_node].append((from_node, distance))

    def dijkstra(self, start_node):
        start_node.distance = 0
        pq = [(0, start_node)]
        while pq:
            curr_dist, curr_node = heapq.heappop(pq)
            if curr_node.name == 'E':
                return curr_dist
            for neighbor, dist in self.edges[curr_node.name]:
                old_dist = self.nodes[neighbor].distance
                new_dist = curr_dist + dist
                if new_dist < old_dist:
                    self.nodes[neighbor].distance = new_dist
                    self.nodes[neighbor].previous = curr_node
                    heapq.heappush(pq, (new_dist, self.nodes[neighbor]))
        return float('inf')

def optimal_route(graph):
    nodes = list(graph.nodes.values())
    start_node = next(node for node in nodes if node.name == 'S')
    end_node = next(node for node in nodes if node.name == 'E')
    route = []
    curr_node = end_node
    while curr_node:
        route.append(curr_node.name)
        curr_node = curr_node.previous
    return list(reversed(route))

def main():
    graph = Graph()
    graph.add_node(Node('S'))
    graph.add_node(Node('A'))
    graph.add_node(Node('B'))
    graph.add_node(Node('C'))
    graph.add_node(Node('D'))
    graph.add_node(Node('E'))
    graph.add_edge('S', 'A', 10)
    graph.add_edge('S', 'B', 15)
    graph.add_edge('A', 'C', 5)
    graph.add_edge('A', 'D', 20)
    graph.add_edge('B', 'D', 15)
    graph.add_edge('C', 'E', 10)
    graph.add_edge('D', 'E', 5)
    shortest_distance = graph.dijkstra('S')
    print(f"Shortest distance: {shortest_distance}")
    optimal_route_path = optimal_route(graph)
    print(f"Optimal route path: {' -> '.join(optimal_route_path)}")

if __name__ == '__main__':
    main()