from ortools.constraint_solver import pywrapcp
import numpy as np
import time

def create_data_model(distances):
    data = {}
    data['num_vehicles'] = 1
    data['index_to_node'] = range(len(distances))
    data['edge_costs'] = distances
    return data

def solve_tsp(data):
    solver = pywrapcp.RoutingIndexManager(len(data['index_to_node']), data['num_vehicles'], 0)
    routing = pywrapcp.RoutingModel(solver)

    for node in range(1, len(data['index_to_node'])):
        from_node = solver.IndexByNode(node - 1)
        to_node = solver.IndexByNode(node)
        routing.AddDimension(
            routing.InAbsorb(from_node),  # From
            0,  # Max slack
            3000,  # Maximum distance per dimension
            True,  # start cumul to zero OR with full load
            'Distance'
        )

    for node in range(len(data['index_to_node'])):
        from_node = solver.IndexByNode(node - 1)
        to_node = solver.IndexByNode(node)
        routing.SetArcCostForIndex(from_node, to_node, data['edge_costs'][node])

    solution = routing.Solve()
    if solution:
        return {'route': [data['index_to_node'][routing.IndexToNode(index)] for index in solution.GetRouteIndexes()]}
    else:
        return None

def main():
    distances = np.random.randint(1, 100, size=(10, 10))
    data = create_data_model(distances)
    start_time = time.time()
    result = solve_tsp(data)
    end_time = time.time()
    print(f"Route: {result['route']}")
    print(f"Total Distance: {sum([distances[i][j] for i, j in zip(result['route'], result['route'][1:])])}")
    print(f"Time taken to solve the TSP: {(end_time - start_time):.2f} seconds")

if __name__ == '__main__':
    main()