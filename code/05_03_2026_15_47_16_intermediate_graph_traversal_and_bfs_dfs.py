from collections import deque

class Graph:
    def __init__(self, num_nodes):
        self.num_nodes = num_nodes
        self.adj_list = {i: [] for i in range(num_nodes)}

    def add_edge(self, node1, node2):
        if node1 < 0 or node1 >= self.num_nodes or node2 < 0 or node2 >= self.num_nodes:
            raise ValueError("Invalid node index")
        self.adj_list[node1].append(node2)
        self.adj_list[node2].append(node1)

    def dfs(self, start_node):
        visited = [False] * self.num_nodes
        self._dfs_helper(start_node, visited)

    def _dfs_helper(self, node, visited):
        if visited[node]:
            return
        print(f"Visiting node {node}")
        visited[node] = True
        for neighbor in self.adj_list[node]:
            self._dfs_helper(neighbor, visited)

    def bfs(self, start_node):
        visited = [False] * self.num_nodes
        queue = deque([start_node])
        visited[start_node] = True
        while queue:
            node = queue.popleft()
            print(f"Visiting node {node}")
            for neighbor in self.adj_list[node]:
                if not visited[neighbor]:
                    queue.append(neighbor)
                    visited[neighbor] = True

if __name__ == '__main__':
    g = Graph(5)  # Create a graph with 5 nodes
    g.add_edge(0, 1)
    g.add_edge(0, 2)
    g.add_edge(1, 3)
    g.add_edge(2, 4)

    print("DFS traversal:")
    g.dfs(0)

    print("\nBFS traversal:")
    g.bfs(0)