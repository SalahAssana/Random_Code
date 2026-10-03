def graph_coloring(graph):
    # Initialize colors for each node as unknown
    colors = [-1] * len(graph)

    def color_node(node):
        # Try to assign a unique color to the node
        for color in range(len(graph)):
            if is_safe(color, node, colors):
                return color

        # If no safe color found, return -1 (unknown)
        return -1

    def is_safe(color, node, colors):
        # Check if neighboring nodes have the same color
        for neighbor in graph[node]:
            if colors[neighbor] == color:
                return False

        # No conflicting colors found, it's safe to assign this color
        return True

    # Start coloring from the first node (0)
    for i in range(len(graph)):
        colors[i] = color_node(i)

    return colors


def main():
    graph = [[1, 2], [0, 3], [0, 2], [1]]
    print("Graph Coloring:", graph_coloring(graph))


if __name__ == '__main__':
    main()