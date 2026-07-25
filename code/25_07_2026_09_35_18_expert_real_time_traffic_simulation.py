import random
from collections import deque
from heapq import heapify, heappop, heappush

class Node:
    def __init__(self, id):
        self.id = id
        self.incoming = set()
        self.outgoing = set()

class TrafficSimulation:
    def __init__(self, nodes, edges):
        self.nodes = {node.id: node for node in nodes}
        self.edges = [(a, b) for a, b in edges]
        heapify([(0, a, b) for a, b in self.edges])

    def run(self):
        while self.edges:
            cost, from_node, to_node = heappop()
            if from_node not in self.nodes[from_node].outgoing or to_node not in self.nodes[to_node].incoming:
                continue
            self.nodes[from_node].outgoing.remove(to_node)
            self.nodes[to_node].incoming.remove(from_node)
            for edge in self.edges[:]:
                a, b = edge
                if (a == from_node and b != to_node) or (b == to_node and a != from_node):
                    heappush((cost + 1, a, b))
                else:
                    self.edges.remove(edge)

    def simulate(self):
        for _ in range(1000):  # run simulation 1000 times
            self.run()
            print(f"Simulation finished. Nodes: {[node.id for node in self.nodes.values()]}")

if __name__ == '__main__':
    nodes = [Node(i) for i in range(10)]
    edges = [(i, (i+1)%10) for i in range(9)]  # simple ring
    traffic_simulation = TrafficSimulation(nodes, edges)
    traffic_simulation.simulate()