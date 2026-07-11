import random
import networkx as nx
import matplotlib.pyplot as plt
import time
from queue import Queue

class TrafficLight:
    def __init__(self):
        self.green = True
        self.time_left = 5

    def update(self):
        if self.green and self.time_left > 0:
            self.time_left -= 1
        else:
            self.green = not self.green
            self.time_left = 3


class Vehicle:
    def __init__(self, id, position, speed):
        self.id = id
        self.position = position
        self.speed = speed

    def move(self):
        if self.position < 100 and self.speed > 0:
            self.position += self.speed
            print(f"Vehicle {self.id} moved to position {self.position}")
        elif self.position >= 100:
            print(f"Vehicle {self.id} reached the end")
        else:
            print(f"Vehicle {self.id} stopped")


class RoadNetwork:
    def __init__(self):
        self.graph = nx.Graph()
        self.traffic_light = TrafficLight()

    def add_vehicle(self, vehicle):
        self.graph.add_node(vehicle.id)
        self.graph.nodes[vehicle.id]['position'] = vehicle.position

    def update_vehicles(self):
        for node in list(self.graph.nodes):
            if 'position' in self.graph.nodes[node]:
                position = int(self.graph.nodes[node]['position'])
                speed = random.randint(1, 5)  # Simulate varying speeds
                self.graph.add_edge(node, str(position + speed), weight=speed)
        for node in list(self.graph.nodes):
            if 'position' not in self.graph.nodes[node]:
                self.graph.remove_node(node)

    def visualize_network(self):
        pos = nx.spring_layout(self.graph)
        nx.draw_networkx(self.graph, pos, with_labels=True, node_size=5000, node_color='lightblue')
        plt.show()

    def run_simulation(self):
        for _ in range(100):  # Run simulation for 100 steps
            self.traffic_light.update()
            if self.traffic_light.green:
                print("Green light")
            else:
                print("Red light")
            for vehicle_id in list(self.graph.nodes):
                vehicle = Vehicle(vehicle_id, int(self.graph.nodes[vehicle_id]['position']), random.randint(1, 5))
                self.add_vehicle(vehicle)
                vehicle.move()
                time.sleep(0.5)  # Simulate time passing
            self.update_vehicles()

    def main(self):
        road_network = RoadNetwork()
        for i in range(10):  # Add vehicles to the network
            road_network.add_vehicle(Vehicle(i, i * 10, random.randint(1, 5)))
        road_network.run_simulation()
        road_network.visualize_network()


if __name__ == '__main__':
    main()