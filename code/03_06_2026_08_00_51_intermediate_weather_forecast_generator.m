% Weather Forecast Generator
%
% This program generates a simple weather forecast based on user inputted city or zip code,
% using real-world data and algorithms.

% Import necessary libraries
import java.io.*;
import java.net.*;

class WeatherForecast {
    public static void main(String[] args) throws IOException {
        % Prompt the user for city or zip code
        System.out.println("Enter a city or zip code:");
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String location = reader.readLine();
        
        % Use OpenWeatherMap API to get weather data
        URL url = new URL("http://api.openweathermap.org/data/2.5/weather?q=" + location + "&units=imperial&appid=YOUR_API_KEY");
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");

        % Check for errors
        if (conn.getResponseCode() != 200) {
            System.out.println("Error: " + conn.getResponseMessage());
            return;
        }

        % Get weather data from API response
        InputStream in = conn.getInputStream();
        BufferedReader br = new BufferedReader(new InputStreamReader(in));
        String line;
        StringBuilder response = new StringBuilder();
        while ((line = br.readLine()) != null) {
            response.append(line);
        }
        br.close();
        in.close();

        % Parse JSON weather data
        JSONObject json = new JSONObject(response.toString());
        double temp = Double.parseDouble(json.getString("main").getJSONObject("temp").toString());
        String condition = json.getJSONArray("weather").getJSONObject(0).getString("description");

        % Generate and print the weather forecast
        System.out.println("Current temperature: " + temp + "°F");
        System.out.println("Weather condition: " + condition);
    }
}