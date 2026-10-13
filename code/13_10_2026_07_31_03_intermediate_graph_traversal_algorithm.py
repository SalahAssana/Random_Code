class Graph:
    def __init__(self):
        self.adj_list = {}

    def add_edge(self, node1, node2):
        if node1 not in self.adj_list:
            self.adj_list[node1] = []
        if node2 not in self.adj_list:
            self.adj_list[node2] = []
        self.adj_list[node1].append(node2)
        self.adj_list[node2].append(node1)

    def DFS(self, start_node):
        visited = set()
        traversal_order = []

        def dfs_helper(node):
            if node not in visited:
                visited.add(node)
                for neighbor in self.adj_list.get(node, []):
                    dfs_helper(neighbor)
                traversal_order.append(node)

        dfs_helper(start_node)
        return traversal_order[::-1]

    def BFS(self, start_node):
        visited = set()
        queue = [start_node]
        traversal_order = []

        while queue:
            node = queue.pop(0)
            if node not in visited:
                visited.add(node)
                for neighbor in self.adj_list.get(node, []):
                    if neighbor not in visited:
                        queue.append(neighbor)
                traversal_order.append(node)

        return traversal_order


if __name__ == '__main__':
    graph = Graph()
    graph.add_edge('A', 'B')
    graph.add_edge('A', 'C')
    graph.add_edge('B', 'D')
    graph.add_edge('C', 'E')
    graph.add_edge('D', 'F')
    graph.add_edge('E', 'F')

    print("Depth-First Traversal (DFS):", graph.DFS('A'))
    print("Breadth-First Traversal (BFS):", graph.BFS('A'))