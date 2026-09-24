# Weather Forecast
# Complexity Level: BEGINNER

temperature = 25  # synthetic data - today's temperature (in degrees Celsius)

weather_conditions = {
    "sunny": None,
    "cloudy": None,
    "rainy": None,
}

if temperature >= 20:
    weather_condition = "sunny"
elif temperature < 15:
    weather_condition = "rainy"
else:
    weather_condition = "cloudy"

print("Today's weather is:", weather_conditions[weather_condition])