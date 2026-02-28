import networkx as nx
import random
from copy import deepcopy

def read_graph(graph_file):
    G = nx.Graph()
    with open(graph_file) as f:
        lines = [line.strip() for line in f.readlines()]
        for line in lines[1:]:
            node1, node2 = map(int, line.split())
            G.add_edge(node1, node2)
    return G

def graph_coloring(G):
    color_map = {}
    colors = list(range(1, min(len(G), 4) + 1))  # Assign a maximum of 3 colors
    for node in G.nodes:
        neighbors = list(G.neighbors(node))
        available_colors = set(colors) - set(color_map.get(n, []) for n in neighbors)
        if not available_colors:  # No color is available, backtrack
            return None
        color_map[node] = min(available_colors)

    return color_map

def print_coloring(graph_file, coloring):
    G = read_graph(graph_file)
    print(f"Coloring for {graph_file}:")
    for node, color in coloring.items():
        print(f"{node}: Color {color}")

if __name__ == '__main__':
    graph_file = "test.graph"
    G = read_graph(graph_file)
    coloring = graph_coloring(G)
    if coloring:
        print_coloring(graph_file, coloring)