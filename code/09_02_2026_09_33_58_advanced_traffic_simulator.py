import heapq
import time
from collections import defaultdict
from threading import Thread, Condition

class Car:
    def __init__(self, id, arrival_time):
        self.id = id
        self.arrival_time = arrival_time
        selfdeparture_time = float('inf')

class Intersection:
    def __init__(self, num_lanes, traffic_light_duration):
        self.num_lanes = num_lanes
        self.traffic_light_duration = traffic_light_duration
        self.cars = []
        self.lanes = defaultdict(list)
        self.lock = Condition()

    def add_car(self, car):
        with self.lock:
            self.cars.append(car)
            lane_idx = (car.arrival_time // 10) % self.num_lanes
            self.lanes[lane_idx].append(car)

    def clear_cars(self):
        with self.lock:
            for lane in self.lanes.values():
                while lane:
                    car = lane.pop(0)
                    if car.departure_time < time.time() + self.traffic_light_duration:
                        continue
                    car.departure_time = time.time()
                    self.cars.remove(car)

    def __repr__(self):
        return f'Intersection({self.num_lanes}, {self.traffic_light_duration})'

class TrafficLight:
    def __init__(self, duration):
        self.duration = duration
        self.on = True

    def toggle(self):
        self.on = not self.on

class Optimizer(Thread):
    def __init__(self, intersection):
        Thread.__init__(self)
        self.intersection = intersection

    def run(self):
        while True:
            with self.intersection.lock:
                self.intersection.clear_cars()
                if not self.intersection.cars:
                    break
                cars_to_depart = []
                for car in sorted(self.intersection.cars, key=lambda c: c.arrival_time):
                    if car.departure_time <= time.time():
                        cars_to_depart.append(car)
                        self.intersection.cars.remove(car)
                with open('traffic.txt', 'a') as f:
                    f.write(f'{time.time()}\n')
                    for car in cars_to_depart:
                        f.write(f'Car {car.id} departed at {car.departure_time}\n')
                time.sleep(self.intersection.traffic_light_duration)

def simulate_traffic(num_cars, num_lanes, traffic_light_duration):
    intersection = Intersection(num_lanes, traffic_light_duration)
    optimizer = Optimizer(intersection)
    for _ in range(num_cars):
        car = Car(_ + 1, time.time())
        intersection.add_car(car)
        time.sleep(0.01)
    optimizer.start()
    while True:
        time.sleep(1)

if __name__ == '__main__':
    simulate_traffic(1000, 4, 5)