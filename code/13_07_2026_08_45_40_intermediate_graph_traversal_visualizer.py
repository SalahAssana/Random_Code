import networkx as nx
import matplotlib.pyplot as plt
import random

class GraphTraverser:
    def __init__(self):
        self.graph = None
        self.traversal_order = []

    def load_graph(self, num_nodes=10, density=0.5):
        self.graph = nx.gnm_random_graph(num_nodes, int(num_nodes * density))
        pos = nx.spring_layout(self.graph)
        labels = {n: str(n) for n in self.graph}
        nx.draw_networkx(self.graph, pos, with_labels=True, node_color='lightblue', edge_color='gray')
        plt.show()

    def dfs_traversal(self):
        visited = set()
        start_node = random.choice(list(self.graph.nodes))
        self.traversal_order.append(start_node)

        def traverse(node):
            if node not in visited:
                visited.add(node)
                self.traversal_order.append(node)
                for neighbor in self.graph.neighbors(node):
                    traverse(neighbor)

        traverse(start_node)
        return self.traversal_order

    def bfs_traversal(self):
        visited = set()
        start_node = random.choice(list(self.graph.nodes))
        queue = [start_node]

        while queue:
            node = queue.pop(0)
            if node not in visited:
                visited.add(node)
                self.traversal_order.append(node)
                for neighbor in self.graph.neighbors(node):
                    if neighbor not in visited:
                        queue.append(neighbor)

        return self.traversal_order

    def visualize_traversal(self, traversal_method):
        if self.graph is None:
            print("No graph loaded. Load a graph first.")
            return
        if traversal_method == "dfs":
            traversal_result = self.dfs_traversal()
        elif traversal_method == "bfs":
            traversal_result = self.bfs_traversal()
        else:
            print(f"Invalid traversal method: {traversal_method}. Choose 'dfs' or 'bfs'.")
            return

        print("Traversal order:", traversal_result)
        plt.figure(figsize=(8, 6))
        pos = nx.spring_layout(self.graph)
        nx.draw_networkx_nodes(self.graph, pos, node_color='lightblue', node_size=500)
        nx.draw_networkx_edges(self.graph, pos, edge_color='gray')
        nx.draw_networkx_labels(self.graph, pos, font_size=10)
        plt.axis('off')
        plt.show()

if __name__ == '__main__':
    traverser = GraphTraverser()
    traverser.load_graph(num_nodes=20, density=0.2)
    traverser.visualize_traversal("dfs")  # or "bfs"