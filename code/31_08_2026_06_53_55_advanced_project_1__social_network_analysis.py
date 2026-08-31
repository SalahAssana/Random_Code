import networkx as nx
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
import numpy as np

class Node:
    def __init__(self, name):
        self.name = name
        self.connections = []

class Edge:
    def __init__(self, node1, node2):
        self.node1 = node1
        self.node2 = node2

def create_network():
    G = nx.Graph()
    
    nodes = [Node(f"Node {i}") for i in range(10)]
    edges = []
    for i in range(5):
        node1 = np.random.choice(nodes)
        node2 = np.random.choice([n for n in nodes if n != node1])
        edge = Edge(node1, node2)
        G.add_edge(node1.name, node2.name)
        edges.append(edge)

    return G, edges

def cluster_network(G):
    # Convert graph to adjacency matrix
    A = nx.to_numpy_array(G)

    # Apply k-means clustering algorithm
    kmeans = KMeans(n_clusters=4)  # Number of clusters
    labels = kmeans.fit_predict(A)

    return labels

def visualize_network(G, edges, labels):
    pos = nx.spring_layout(G)
    
    plt.figure(figsize=(8, 6))
    nx.draw_networkx(G, pos, node_size=5000, with_labels=True)
    
    for edge in edges:
        if (edge.node1.name, edge.node2.name) in G.edges():
            nx.draw_networkx_edge_labels(G, pos, {(edge.node1.name, edge.node2.name): f"{edge}"})


    plt.show()

def main():
    if __name__ == '__main__':
        G, edges = create_network()
        labels = cluster_network(G)
        visualize_network(G, edges, labels)

if __name__ == '__main__':