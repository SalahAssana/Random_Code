import heapq
from collections import deque

class Graph:
    def __init__(self):
        self.adj_list = {}

    def add_edge(self, node1, node2, weight=1):
        if node1 not in self.adj_list:
            self.adj_list[node1] = []
        if node2 not in self.adj_list:
            self.adj_list[node2] = []

        self.adj_list[node1].append((node2, weight))
        self.adj_list[node2].append((node1, weight))

    def dijkstra(self, start_node):
        distances = {node: float('inf') for node in self.adj_list}
        distances[start_node] = 0
        pq = [(0, start_node)]

        while pq:
            current_distance, current_node = heapq.heappop(pq)

            if current_distance > distances[current_node]:
                continue

            for neighbor, weight in self.adj_list[current_node]:
                old_distance = distances[neighbor]
                new_distance = current_distance + weight
                if new_distance < old_distance:
                    distances[neighbor] = new_distance
                    heapq.heappush(pq, (new_distance, neighbor))

        return distances

    def a_star_search(self, start_node, end_node):
        distances = {node: float('inf') for node in self.adj_list}
        distances[start_node] = 0
        pq = [(0, start_node, [])]

        while pq:
            current_distance, current_node, path = heapq.heappop(pq)

            if current_distance > distances[current_node]:
                continue

            if current_node == end_node:
                return (current_distance, path + [end_node])

            for neighbor, weight in self.adj_list[current_node]:
                old_distance = distances[neighbor]
                new_distance = current_distance + weight
                if new_distance < old_distance:
                    distances[neighbor] = new_distance
                    heapq.heappush(pq, (new_distance, neighbor, path + [current_node]))

        return None

    def dijkstra_bidirectional(self, start_node, end_node):
        distances_start_to_end = {node: float('inf') for node in self.adj_list}
        distances_end_to_start = {node: float('inf') for node in self.adj_list}

        distances_start_to_end[start_node] = 0
        distances_end_to_start[end_node] = 0

        queue_start_to_end = [(0, start_node)]
        queue_end_to_start = [(0, end_node)]

        while queue_start_to_end and queue_end_to_start:
            current_distance_start_to_end, node_start_to_end = heapq.heappop(queue_start_to_end)
            current_distance_end_to_start, node_end_to_start = heapq.heappop(queue_end_to_start)

            if current_distance_start_to_end > distances_start_to_end[node_start_to_end] or \
               current_distance_end_to_start > distances_end_to_start[node_end_to_start]:
                continue

            for neighbor, weight in self.adj_list[node_start_to_end]:
                old_distance = distances_start_to_end[neighbor]
                new_distance = current_distance_start_to_end + weight
                if new_distance < old_distance:
                    distances_start_to_end[neighbor] = new_distance
                    heapq.heappush(queue_start_to_end, (new_distance, neighbor))

            for neighbor, weight in self.adj_list[node_end_to_start]:
                old_distance = distances_end_to_start[neighbor]
                new_distance = current_distance_end_to_start + weight
                if new_distance < old_distance:
                    distances_end_to_start[neighbor] = new_distance
                    heapq.heappush(queue_end_to_start, (new_distance, neighbor))

        shortest_path = None
        for node in self.adj_list:
            if distances_start_to_end[node] != float('inf') and distances_end_to_start[node] != float('inf'):
                total_distance = distances_start_to_end[node] + distances_end_to_start[node]
                if shortest_path is None or total_distance < shortest_path[0]:
                    shortest_path = (total_distance, node)

        return shortest_path

    def breadth_first_search(self, start_node):
        visited = set()
        queue = deque([start_node])
        parent = {node: None for node in self.adj_list}

        while queue:
            node = queue.popleft()
            if node not in visited:
                visited.add(node)
                for neighbor, _ in self.adj_list[node]:
                    if neighbor not in visited:
                        queue.append(neighbor)
                        parent[neighbor] = node

        return parent


if __name__ == '__main__':
    graph = Graph()
    graph.add_edge('A', 'B', 2)
    graph.add_edge('A', 'C', 3)
    graph.add_edge('B', 'C', 1)
    graph.add_edge('B', 'D', 4)
    graph.add_edge('C', 'D', 5)

    print(graph.dijkstra('A'))
    print(graph.a_star_search('A', 'D'))
    shortest_path = graph.dijkstra_bidirectional('A', 'D')
    if shortest_path:
        print(f"Shortest path: {shortest_path[1]}")
    else:
        print("No shortest path found.")

    parent = graph.breadth_first_search('A')
    print(parent)