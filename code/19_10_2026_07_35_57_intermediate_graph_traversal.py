# Graph Traversal in Python

class Node:
    def __init__(self, value):
        self.value = value
        self.children = []

def dfs(node, visited=None):
    if visited is None:
        visited = set()
    visited.add(node.value)
    print(f"Visiting {node.value}")
    for child in node.children:
        if child.value not in visited:
            dfs(child, visited)

def bfs(root, visited=None):
    if visited is None:
        visited = set()
    queue = [root]
    while queue:
        node = queue.pop(0)
        print(f"Visiting {node.value}")
        if node.value not in visited:
            visited.add(node.value)
            queue.extend([child for child in node.children if child.value not in visited])

# Testing the code
graph = [Node(i) for i in range(9)]
for i, parent in enumerate(graph):
    graph[i].children = [node for j, node in enumerate(graph) if (j % 3 == i and j != i)]

print("Depth-First Search:")
dfs(graph[0])
print("\nBreadth-First Search:")
bfs(graph[0])

if __name__ == '__main__':
    pass