# Weather Forecast System

# Import necessary modules
import random

def get_weather_forecast(location, weather_condition):
    # Simple forecast based on location and weather condition
    if location == "New York" and weather_condition == "Sunny":
        return "Partly cloudy with a high of 75F"
    elif location == "Los Angeles" and weather_condition == "Rainy":
        return "Overcast with a high of 65F"
    elif location == "Chicago" and weather_condition == "Cloudy":
        return "Mostly sunny with a high of 70F"
    else:
        return "Forecast not available"

def main():
    # Ask user for location and weather condition
    location = input("Enter your location: ")
    weather_condition = input("Enter the current weather condition (Sunny, Rainy, Cloudy): ")

    # Get the weather forecast based on user input
    forecast = get_weather_forecast(location, weather_condition)

    # Print the weather forecast
    print(f"Your {weather_condition} day in {location} will be: {forecast}")

if __name__ == '__main__':
    main()