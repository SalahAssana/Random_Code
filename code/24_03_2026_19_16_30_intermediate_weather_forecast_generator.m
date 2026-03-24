% Weather Forecast Generator
%
% This program generates weather forecasts based on user input.

% Import necessary libraries
import java.util.*

class WeatherForecast {
    // Define constants for different weather conditions
    static final String SUNNY = "Sunny";
    static final String RAINY = "Rainy";
    static final String CLOUDY = "Cloudy";

    // Constructor to initialize the forecast object
    public WeatherForecast(String location, int temperature) {
        this.location = location;
        this.temperature = temperature;
        this.weatherCondition = getRandomWeather();
    }

    // Method to generate a random weather condition
    private String getRandomWeather() {
        Random rand = new Random();
        double randomValue = rand.nextDouble();

        if (randomValue < 0.3) {
            return SUNNY;
        } else if (randomValue < 0.7) {
            return CLOUDY;
        } else {
            return RAINY;
        }
    }

    // Method to generate a weather forecast based on the temperature
    public String getWeatherForecast() {
        if (temperature > 25) {
            return "It's going to be " + weatherCondition + " in " + location + ". Don't forget your sunscreen!";
        } else if (temperature < 15) {
            return "It's going to be " + weatherCondition + " in " + location + ". Bring a jacket!";
        } else {
            return "The weather is expected to be " + weatherCondition + " in " + location + ".";
        }
    }

    // Instance variables
    private String location;
    private int temperature;
    private String weatherCondition;

    public static void main(String[] args) {
        // Create a WeatherForecast object with user input
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the location: ");
        String location = scanner.nextLine();
        System.out.println("Enter the temperature: ");
        int temperature = scanner.nextInt();

        WeatherForecast forecast = new WeatherForecast(location, temperature);

        // Print the weather forecast
        System.out.println(forecast.getWeatherForecast());
    }
}