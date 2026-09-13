import heapq
from typing import List, Tuple
import networkx as nx
import matplotlib.pyplot as plt
from mpl_toolkits.basemap import Basemap

class TrafficNode:
    def __init__(self, name: str):
        self.name = name
        self.neighbors = []
        self.weight = 0.0

class Graph:
    def __init__(self):
        self.nodes = []

    def add_node(self, node: TrafficNode):
        self.nodes.append(node)

    def add_edge(self, from_node: TrafficNode, to_node: TrafficNode, weight: float):
        from_node.neighbors.append(to_node)
        to_node.neighbors.append(from_node)
        from_node.weight += weight
        to_node.weight += weight

def dijkstra(graph: Graph, start_node: TrafficNode) -> Tuple[dict, dict]:
    unvisited = [(0, start_node)]
    shortest_path = {}
    previous_nodes = {}

    while unvisited:
        (cost, current_node) = heapq.heappop(unvisited)

        for neighbor in current_node.neighbors:
            old_cost = neighbor.weight
            new_cost = cost + 1.0

            if new_cost < old_cost:
                shortest_path[neighbor.name] = new_cost
                previous_nodes[neighbor.name] = current_node.name
                heapq.heappush(unvisited, (new_cost, neighbor))

    return shortest_path, previous_nodes

def find_optimal_route(graph: Graph, start_node: TrafficNode, end_node: TrafficNode) -> List[Tuple[str, str]]:
    _, previous_nodes = dijkstra(graph, start_node)

    route = []
    current_node_name = end_node.name
    while current_node_name != start_node.name:
        route.append((current_node_name, previous_nodes[current_node_name]))
        current_node_name = previous_nodes[current_node_name]

    return list(reversed(route))

def draw_map(graph: Graph):
    fig, ax = plt.subplots()
    m = Basemap(llcrnrlon=0,llcrnrlat=-90,urcrnrlon=180,urcrnrlat=0,
                lat_0=-30,lon_0=0,projection='gnom',lat_1=-30)

    x,y = zip(*[(node.name.split(',')[1], node.name.split(',')[0]) for node in graph.nodes])
    m.plot(x, y, 'k,')
    plt.show()

def main():
    if __name__ == '__main__':
        graph = Graph()

        node_a = TrafficNode('A,40')
        node_b = TrafficNode('B,30')
        node_c = TrafficNode('C,20')
        node_d = TrafficNode('D,10')

        graph.add_node(node_a)
        graph.add_node(node_b)
        graph.add_node(node_c)
        graph.add_node(node_d)

        graph.add_edge(node_a, node_b, 5.0)
        graph.add_edge(node_b, node_c, 3.0)
        graph.add_edge(node_c, node_d, 2.0)
        graph.add_edge(node_d, node_b, 4.0)
        graph.add_edge(node_a, node_c, 6.0)

        shortest_path, previous_nodes = dijkstra(graph, node_a)

        optimal_route = find_optimal_route(graph, node_a, node_d)

        print("Shortest Path:", shortest_path)
        print("Optimal Route:", optimal_route)

        draw_map(graph)

if __name__ == '__main__':
    main()