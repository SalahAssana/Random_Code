def find_available_color(graph, color_map, current_node):
    for i in range(len(color_map)):
        if all((graph[current_node][j] and i != color_map[j]) for j in range(len(graph))):
            return i
    return None

def graph_coloring(graph):
    num_nodes = len(graph)
    color_map = [None] * num_nodes
    for node in range(num_nodes):
        available_colors = list(range(len(color_map)))
        while available_colors:
            current_color = find_available_color(graph, color_map, node)
            if current_color is not None:
                color_map[node] = current_color
                available_colors.remove(current_color)
            else:
                break
    return color_map

# Example usage
if __name__ == '__main__':
    graph = [[1, 0, 1], [1, 1, 0], [1, 0, 1]]
    print(graph_coloring(graph))