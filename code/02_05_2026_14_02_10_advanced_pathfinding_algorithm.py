import heapq

class Graph:
    def __init__(self):
        self.adj_list = {}

    def add_edge(self, node1, node2, weight):
        if node1 not in self.adj_list:
            self.adj_list[node1] = []
        if node2 not in self.adj_list:
            self.adj_list[node2] = []

        self.adj_list[node1].append((node2, weight))
        self.adj_list[node2].append((node1, weight))

    def dijkstra(self, start, end):
        queue = [(0, start)]
        distances = {node: float('inf') for node in self.adj_list}
        distances[start] = 0
        previous = {}

        while queue:
            (dist, current_node) = heapq.heappop(queue)

            if dist > distances[current_node]:
                continue

            for neighbor, neighbor_dist in self.adj_list.get(current_node, []):
                old_dist = distances[neighbor]
                new_dist = dist + neighbor_dist
                if new_dist < old_dist:
                    distances[neighbor] = new_dist
                    previous[neighbor] = current_node
                    heapq.heappush(queue, (new_dist, neighbor))

        return distances[end], previous


# Example usage
if __name__ == '__main__':
    graph = Graph()
    graph.add_edge('A', 'B', 2)
    graph.add_edge('A', 'C', 3)
    graph.add_edge('B', 'D', 1)
    graph.add_edge('B', 'E', 4)
    graph.add_edge('C', 'F', 5)
    graph.add_edge('D', 'E', 2)
    graph.add_edge('E', 'F', 3)

    shortest_distance, previous = graph.dijkstra('A', 'F')

    print("Shortest distance from A to F:", shortest_distance)
    path = []
    current_node = 'F'
    while current_node != 'A':
        path.append(current_node)
        current_node = previous[current_node]
    path.append('A')
    path.reverse()
    print("Shortest path:", ' -> '.join(path))