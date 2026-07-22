import collections

class Graph:
    def __init__(self):
        self.adj_list = collections.defaultdict(list)

    def add_edge(self, node1, node2):
        self.adj_list[node1].append(node2)
        self.adj_list[node2].append(node1)

    def bfs(self, start_node):
        visited = set()
        queue = [start_node]
        traversal_order = []

        while queue:
            node = queue.pop(0)
            if node not in visited:
                visited.add(node)
                traversal_order.append(node)
                queue.extend(neighbor for neighbor in self.adj_list[node] if neighbor not in visited)

        return traversal_order

    def dfs(self, start_node):
        visited = set()
        traversal_order = []

        def _dfs(node):
            visited.add(node)
            traversal_order.append(node)
            for neighbor in self.adj_list[node]:
                if neighbor not in visited:
                    _dfs(neighbor)

        _dfs(start_node)
        return traversal_order

# Example usage
if __name__ == '__main__':
    graph = Graph()
    graph.add_edge('A', 'B')
    graph.add_edge('A', 'C')
    graph.add_edge('B', 'D')
    graph.add_edge('C', 'E')
    graph.add_edge('D', 'F')
    graph.add_edge('E', 'F')

    print("BFS traversal order:", graph.bfs('A'))
    print("DFS traversal order:", graph.dfs('A'))