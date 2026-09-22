import heapq
from collections import deque

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

    def bfs(self, start):
        visited = set()
        queue = deque([start])
        visited.add(start)

        while queue:
            node = queue.popleft()
            print(node, end=' ')

            for neighbor in self.adj_list.get(node, []):
                if neighbor not in visited:
                    queue.append(neighbor)
                    visited.add(neighbor)

    def dijkstra(self, start, end):
        pq = [(0, start)]
        distances = {node: float('inf') for node in self.adj_list}
        distances[start] = 0

        while pq:
            (dist, current_node) = heapq.heappop(pq)

            if current_node == end:
                return dist

            if dist > distances[current_node]:
                continue

            for neighbor in self.adj_list.get(current_node, []):
                old_dist = distances[neighbor]
                new_dist = dist + 1
                if new_dist < old_dist:
                    distances[neighbor] = new_dist
                    heapq.heappush(pq, (new_dist, neighbor))

        return -1

if __name__ == '__main__':
    graph = Graph()
    graph.add_edge('A', 'B')
    graph.add_edge('A', 'C')
    graph.add_edge('B', 'D')
    graph.add_edge('B', 'E')
    graph.add_edge('C', 'F')
    graph.add_edge('D', 'E')

    print("BFS Traversal: ", end='')
    graph.bfs('A')
    print()

    start_node = 'A'
    end_node = 'E'

    shortest_distance = graph.dijkstra(start_node, end_node)
    if shortest_distance != -1:
        print(f"The shortest distance from {start_node} to {end_node} is {shortest_distance}")
    else:
        print(f"There is no path from {start_node} to {end_node}")