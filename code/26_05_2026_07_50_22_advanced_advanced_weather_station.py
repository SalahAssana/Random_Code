import numpy as np
from datetime import datetime
from collections import deque

class Sensor:
    def __init__(self, name):
        self.name = name
        self.data = deque(maxlen=100)

    def add_data(self, value):
        self.data.append(value)

    def get_average(self):
        return sum(self.data) / len(self.data)

class WeatherStation:
    def __init__(self):
        self.sensors = [
            Sensor("Temperature"),
            Sensor("Humidity"),
            Sensor("Wind Speed")
        ]
        self.processing_queue = deque()

    def add_data(self, sensor_name, value):
        for sensor in self.sensors:
            if sensor.name == sensor_name:
                sensor.add_data(value)
                break
        else:
            print(f"Sensor {sensor_name} not found.")

    def process_data(self):
        while len(self.processing_queue) > 0:
            data_point = self.processing_queue.popleft()
            temperature = self.sensors[0].get_average()
            humidity = self.sensors[1].get_average()
            wind_speed = self.sensors[2].get_average()

            if data_point["temperature"] < temperature - 5 or data_point["temperature"] > temperature + 5:
                print("Temperature anomaly detected.")
            elif data_point["humidity"] < humidity - 10 or data_point["humidity"] > humidity + 10:
                print("Humidity anomaly detected.")
            elif wind_speed > 50 and data_point["wind speed"] > 100:
                print("Wind speed anomaly detected.")

    def run(self):
        while True:
            sensor_name = input("Enter a sensor name (or 'quit' to stop): ")
            if sensor_name.lower() == "quit":
                break
            value = float(input(f"Enter {sensor_name} value: "))
            self.add_data(sensor_name, value)
            self.processing_queue.append({"temperature": 25.0, "humidity": 50.0, "wind speed": 30.0})
        self.process_data()

if __name__ == '__main__':
    station = WeatherStation()
    station.run()