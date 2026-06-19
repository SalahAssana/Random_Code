# Weather Forecast App
import random

class City:
    def __init__(self, name):
        self.name = name
        self.weather_conditions = ["Sunny", "Cloudy", "Rainy"]

class WeatherForecast:
    def __init__(self):
        self.cities = []

    def add_city(self, city_name):
        self.cities.append(City(city_name))

    def get_weather_forecast(self, city_name):
        for city in self.cities:
            if city.name == city_name:
                return random.choice(city.weather_conditions)
        return "City not found"

def main():
    forecast = WeatherForecast()
    while True:
        print("1. Add City")
        print("2. Get Weather Forecast")
        print("3. Exit")
        choice = input("Enter your choice: ")
        if choice == "1":
            city_name = input("Enter the name of the city: ")
            forecast.add_city(city_name)
        elif choice == "2":
            city_name = input("Enter the name of the city: ")
            print(f"Weather forecast for {city_name}: {forecast.get_weather_forecast(city_name)}")
        elif choice == "3":
            break
        else:
            print("Invalid choice. Please try again.")

if __name__ == '__main__':
    main()