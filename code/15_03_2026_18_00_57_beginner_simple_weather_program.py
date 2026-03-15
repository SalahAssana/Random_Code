# Simple Weather Program

weather_data = {
    "sunny": {"description": "Sunny", "forecast": "Partly cloudy tomorrow"},
    "rainy": {"description": "Rainy", "forecast": "More rain on Thursday"},
    "cloudy": {"description": "Cloudy", "forecast": "No change expected"}
}

def get_weather():
    # Ask user for weather type
    weather_type = input("Enter the weather (sunny, rainy, cloudy): ")
    
    if weather_type in weather_data:
        return weather_data[weather_type]
    else:
        return {"description": "Unknown", "forecast": "Check back later"}

def display_weather(weather):
    print(f"Current weather: {weather['description']}")
    print(f"Forecast: {weather['forecast']}")

if __name__ == '__main__':
    weather = get_weather()
    display_weather(weather)