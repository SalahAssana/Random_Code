# Simple Weather Forecast Program

import random

if __name__ == '__main__':
    print("Simple Weather Forecast Program")
    
    # Ask for user input (city name)
    city = input("Enter your city name: ")
    
    # Generate random weather data
    current_weather = random.choice(["Sunny", "Cloudy", "Rainy"])
    forecast1 = random.choice(["Warm", "Cool", "Partly Cloudy"])
    forecast2 = random.choice(["Windy", "Calm", "Mostly Sunny"])
    
    print(f"Current weather in {city}: {current_weather}")
    print(f"Weather Forecast for {city} (next 2 days):")
    print(f"Day 1: {forecast1}")
    print(f"Day 2: {forecast2}")