# Weather Station
import random

class WeatherStation:
    def __init__(self):
        self.temperature_data = []
        self.humidity_data = []
        self.wind_speed_data = []

    def read_temperature(self):
        return random.uniform(20, 30)

    def read_humidity(self):
        return random.uniform(40, 60)

    def read_wind_speed(self):
        return random.uniform(5, 10)

    def collect_data(self, num_readings):
        for _ in range(num_readings):
            self.temperature_data.append(self.read_temperature())
            self.humidity_data.append(self.read_humidity())
            self.wind_speed_data.append(self.read_wind_speed())

    def display_data(self):
        print("Temperature Data:")
        print(self.temperature_data)
        print("\nHumidity Data:")
        print(self.humidity_data)
        print("\nWind Speed Data:")
        print(self.wind_speed_data)

def main():
    weather_station = WeatherStation()
    weather_station.collect_data(10)
    weather_station.display_data()

if __name__ == '__main__':
    main()