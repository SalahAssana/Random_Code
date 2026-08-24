def print_graph(graph):
    for i in range(len(graph)):
        for j in range(len(graph[0])):
            if graph[i][j] != 0:
                print(f"({i}, {j}) : {graph[i][j]}")
        print()

def dfs(graph, start_vertex):
    visited = [False] * len(graph)
    traversal_order = []

    def dfs_helper(vertex):
        visited[vertex] = True
        traversal_order.append(vertex)
        for neighbor, weight in enumerate(graph[vertex]):
            if not visited[neighbor]:
                dfs_helper(neighbor)

    dfs_helper(start_vertex)
    return traversal_order

def bfs(graph, start_vertex):
    visited = [False] * len(graph)
    traversal_order = []
    queue = []

    def bfs_helper():
        while queue:
            vertex = queue.pop(0)
            if not visited[vertex]:
                visited[vertex] = True
                traversal_order.append(vertex)
                for neighbor, weight in enumerate(graph[vertex]):
                    if not visited[neighbor]:
                        queue.append(neighbor)

    queue.append(start_vertex)
    bfs_helper()
    return traversal_order

# Synthetic data
graph = [[0, 3, 2, 0],
         [0, 0, 1, 4],
         [5, 0, 0, 1],
         [0, 3, 0, 0]]

if __name__ == '__main__':
    print("Graph:")
    print_graph(graph)

    start_vertex = 0
    dfs_order = dfs(graph, start_vertex)
    print(f"DFS Traversal Order: {dfs_order}")

    bfs_order = bfs(graph, start_vertex)
    print(f"BFS Traversal Order: {bfs_order}")