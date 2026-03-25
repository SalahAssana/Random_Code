import random
import time

# Define weather station data types
class WeatherData:
    def __init__(self):
        self.temperature = 0
        self.humidity = 0
        self.wind_speed = 0
        self.precipitation = ""

    # Generate random weather data
    def generate(self):
        self.temperature = round(random.uniform(10, 30), 2)
        self.humidity = random.randint(20, 80)
        self.wind_speed = round(random.uniform(0.5, 3), 2)
        if random.random() < 0.1:
            self.precipitation = "Rain"
        elif random.random() < 0.5:
            self.precipitation = "Cloudy"
        else:
            self.precipitation = "Sunny"

    # Print weather data
    def print(self):
        print(f"Temperature: {self.temperature}°C")
        print(f"Humidity: {self.humidity}%")
        print(f"Wind Speed: {self.wind_speed} m/s")
        print(f"Precipitation: {self.precipitation}")

# Create weather station instance
weather = WeatherData()

if __name__ == '__main__':
    while True:
        # Generate and print new weather data every 5 seconds
        weather.generate()
        weather.print()
        time.sleep(5)