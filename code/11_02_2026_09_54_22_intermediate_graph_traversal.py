class Graph:
    def __init__(self):
        self.graph = {}

    def add_edge(self, node1, node2):
        if node1 not in self.graph:
            self.graph[node1] = [node2]
        else:
            self.graph[node1].append(node2)

        if node2 not in self.graph:
            self.graph[node2] = [node1]
        else:
            self.graph[node2].append(node1)

    def dfs(self, start):
        visited = set()
        traversal_order = []

        def dfs_helper(node):
            visited.add(node)
            traversal_order.append(node)

            if node in self.graph:
                for neighbor in self.graph[node]:
                    if neighbor not in visited:
                        dfs_helper(neighbor)

        dfs_helper(start)

        return traversal_order

# Test the graph and DFS
if __name__ == '__main__':
    g = Graph()
    g.add_edge('A', 'B')
    g.add_edge('A', 'C')
    g.add_edge('B', 'D')
    g.add_edge('C', 'E')
    g.add_edge('D', 'F')

    print("Depth First Search traversal order: ")
    print(g.dfs('A'))