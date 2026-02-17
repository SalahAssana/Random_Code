# graph_matching.py

import networkx as nx
from scipy.spatial import distance

class Node:
    def __init__(self, id):
        self.id = id
        self.features = {}

class Edge:
    def __init__(self, node1, node2, weight):
        self.node1 = node1
        self.node2 = node2
        self.weight = weight

def load_graph(filename):
    graph = nx.Graph()
    with open(filename, 'r') as f:
        for line in f:
            nodes = line.strip().split(',')
            if len(nodes) == 3:
                node1_id, node2_id, edge_weight = int(nodes[0]), int(nodes[1]), float(nodes[2])
                graph.add_edge(Node(node1_id), Node(node2_id), weight=edge_weight)
    return graph

def compute_node_features(graph):
    for node in graph.nodes():
        node.features['id'] = node.id
        node.features['degree'] = len(list(graph.neighbors(node)))
        node.features['eccentricity'] = max(distance.euclidean((0, 0), (node1.id, node2.id)) for node1, node2 in graph.edges(node))

def match_nodes(graph1, graph2):
    matched_edges = []
    unmatched_nodes = [list(graph1.nodes()), list(graph2.nodes())]
    while any(unmatched_nodes):
        min_distance = float('inf')
        best_node = None
        best_match = None
        for node in unmatched_nodes[0]:
            for other_node in unmatched_nodes[1]:
                if all(feature in node.features and feature not in other_node.features for feature in ['degree', 'eccentricity']):
                    distance_value = sum(abs(node.features[feature] - other_node.features.get(feature, 0)) for feature in ['id'])
                    if distance_value < min_distance:
                        min_distance = distance_value
                        best_node = node
                        best_match = other_node
        matched_edges.append((best_node, best_match))
        unmatched_nodes[0].remove(best_node)
        unmatched_nodes[1].remove(best_match)
    return matched_edges

if __name__ == '__main__':
    graph1 = load_graph('graph1.txt')
    graph2 = load_graph('graph2.txt')
    compute_node_features(graph1)
    compute_node_features(graph2)
    matched_edges = match_nodes(graph1, graph2)
    print(matched_edges)