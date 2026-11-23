import numpy as np
from scipy.optimize import linear_sum_assignment
from collections import deque

class City:
    def __init__(self, name):
        self.name = name
        self.distance = {}

class RoutePlanner:
    def __init__(self, cities):
        self.cities = {city.name: city for city in cities}

    def calculate_distances(self):
        distances = np.zeros((len(self.cities), len(self.cities)))
        for i, (name1, _) in enumerate(self.cities.items()):
            for j, (name2, _) in enumerate(self.cities.items()):
                if i != j:
                    distances[i, j] = self.cities[list(self.cities.keys())[i]].distance.get(name2, float('inf'))
        return distances

    def find_path(self):
        distances = self.calculate_distances()
        row_ind, col_ind = linear_sum_assignment(distances)
        path = [list(self.cities.keys())[row_ind[0]]]
        visited = set(row_ind[0])
        queue = deque([(row_ind[0], 0)])
        while queue:
            city_index, distance = queue.popleft()
            if city_index in visited:
                continue
            visited.add(city_index)
            for neighbor_index, neighbor_distance in enumerate(distances[city_index]):
                if neighbor_index not in visited and neighbor_distance > 0:
                    queue.append((neighbor_index, neighbor_distance))
        return path

def main():
    cities = [City('A'), City('B'), City('C'), City('D')]
    for i, city in enumerate(cities):
        for j, other_city in enumerate(cities):
            if i != j:
                distance = np.random.randint(1, 10)
                cities[i].distance[other_city.name] = distance
                cities[j].distance[cities[i].name] = distance

    planner = RoutePlanner(cities)
    path = planner.find_path()
    print(path)

if __name__ == '__main__':
    main()