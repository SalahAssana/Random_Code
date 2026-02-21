import networkx as nx
import random
import time
from heapq import heapify, heappop, heappush

class TrafficLight:
    def __init__(self):
        self.phase = "green"

    def change_phase(self):
        if self.phase == "green":
            self.phase = "red"
        elif self.phase == "red":
            self.phase = "green"

    def is_green(self):
        return self.phase == "green"


class Intersection:
    def __init__(self, traffic_light: TrafficLight):
        self.traffic_light = traffic_light
        self.cars_waiting = 0

    def add_car(self):
        if not self.traffic_light.is_green():
            self.cars_waiting += 1

    def remove_car(self):
        self.cars_waiting -= 1


class Road:
    def __init__(self, length: int):
        self.length = length
        self.cars = []

    def add_car(self, speed: float):
        car_length = 10.0  # meters
        self.cars.append((speed, car_length))

    def remove_car(self):
        if self.cars:
            _, car_length = self.cars.pop(0)

    def simulate(self):
        for _ in range(int(self.length / 50)):  # 50m per second
            speed, car_length = random.choice(self.cars)
            distance_traveled = min(speed * 1.0, car_length)  # meters
            self.remove_car()
            if distance_traveled < car_length:
                self.add_car(speed)


class TrafficSimulator:
    def __init__(self):
        self.intersections = {}
        self.roads = []

    def add_intersection(self, intersection_id: int):
        self.intersections[intersection_id] = Intersection(TrafficLight())

    def add_road(self, road_id: int, length: int):
        self.roads.append((road_id, Road(length)))

    def simulate(self):
        for _ in range(60):  # 1 minute
            for intersection_id, intersection in self.intersections.items():
                if random.random() < 0.5:
                    intersection.add_car()
            for road_id, road in self.roads:
                road.simulate()

    def print_status(self):
        for intersection_id, intersection in self.intersections.items():
            print(f"Intersection {intersection_id}: {intersection.cars_waiting} cars waiting")
        for road_id, road in self.roads:
            print(f"Road {road_id}: {len(road.cars)} cars on the road")


if __name__ == '__main__':
    simulator = TrafficSimulator()
    simulator.add_intersection(1)
    simulator.add_road(1, 1000)
    simulator.add_road(2, 500)

    start_time = time.time()
    for _ in range(10):
        simulator.simulate()
        simulator.print_status()
        time.sleep(1)  # wait 1 second between each simulation

    print(f"Simulation took {time.time() - start_time} seconds")