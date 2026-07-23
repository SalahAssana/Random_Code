#include <stdio.h>

int main() {
    // Declare variables for Fahrenheit and Celsius temperatures
    float fahrenheit;
    float celsius;

    // Prompt user to enter temperature in Fahrenheit
    printf("Enter temperature in Fahrenheit: ");
    scanf("%f", &fahrenheit);

    // Convert Fahrenheit to Celsius using arithmetic operation
    celsius = (fahrenheit - 32) * 5.0/9.0;

    // Display the converted Celsius temperature
    printf("%.2f degrees Fahrenheit is equal to %.2f degrees Celsius\n", fahrenheit, celsius);

    return 0;
}