from collections import deque

class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.adj_list = [[] for _ in range(vertices)]

    def add_edge(self, u, v, w):
        self.adj_list[u].append((v, w))

    def DFS(self, start_vertex):
        visited = [False] * self.V
        stack = [start_vertex]
        visited[start_vertex] = True

        while stack:
            vertex = stack.pop()
            print(vertex, end=' ')

            for neighbor, _ in self.adj_list[vertex]:
                if not visited[neighbor]:
                    stack.append(neighbor)
                    visited[neighbor] = True

    def BFS(self, start_vertex):
        visited = [False] * self.V
        queue = deque([start_vertex])
        visited[start_vertex] = True

        while queue:
            vertex = queue.popleft()
            print(vertex, end=' ')

            for neighbor, _ in self.adj_list[vertex]:
                if not visited[neighbor]:
                    queue.append(neighbor)
                    visited[neighbor] = True


if __name__ == '__main__':
    graph = Graph(6)

    graph.add_edge(0, 1, 1)
    graph.add_edge(0, 2, 3)
    graph.add_edge(1, 3, 2)
    graph.add_edge(1, 4, 5)
    graph.add_edge(2, 4, 2)
    graph.add_edge(3, 4, 1)

    print("DFS traversal:")
    graph.DFS(0)
    print()

    print("BFS traversal:")
    graph.BFS(0)