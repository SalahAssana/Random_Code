import requests
import json
from typing import Dict, List

class WeatherForecast:
    def __init__(self):
        self.api_key = "YOUR_API_KEY_HERE"
        self.api_base_url = "http://api.openweathermap.org/data/2.5/weather"

    def get_weather(self, city_name: str) -> Dict:
        try:
            response = requests.get(f"{self.api_base_url}?q={city_name}&units=imperial&appid={self.api_key}")
            if response.status_code == 200:
                return json.loads(response.text)
            else:
                raise Exception("Failed to retrieve weather data")
        except requests.exceptions.RequestException as e:
            print(f"Error: {e}")

    def display_weather(self, city_name: str) -> None:
        weather_data = self.get_weather(city_name)
        if weather_data:
            print(f"Weather in {city_name}:")
            print(f"  Temperature: {weather_data['main']['temp']}°F")
            print(f"  Conditions: {weather_data['weather'][0]['description']}")
            print(f"  Humidity: {weather_data['main']['humidity']}%")

def main():
    if __name__ == '__main__':
        forecast = WeatherForecast()
        city_names = ["New York", "Los Angeles", "Chicago"]
        for city in city_names:
            forecast.display_weather(city)

if __name__ == '__main__':
    main()