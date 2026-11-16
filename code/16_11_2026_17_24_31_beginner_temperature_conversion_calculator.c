#include <stdio.h>

int main() {
    int choice;
    float celsius, fahrenheit, kelvin;

    printf("Temperature Conversion Calculator\n");
    printf("1. Celsius to Fahrenheit/Kelvin\n");
    printf("2. Fahrenheit to Celsius/Kelvin\n");
    printf("3. Kelvin to Celsius/Fahrenheit\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter temperature in Celsius: ");
            scanf("%f", &celsius);
            fahrenheit = celsius * 9/5 + 32;
            kelvin = celsius + 273.15;
            printf("%.2f°C is equal to %.2f°F and %.2fK\n", celsius, fahrenheit, kelvin);
            break;

        case 2:
            printf("Enter temperature in Fahrenheit: ");
            scanf("%f", &fahrenheit);
            celsius = (fahrenheit - 32) * 5/9;
            kelvin = (fahrenheit - 32) * 5/9 + 273.15;
            printf("%.2f°F is equal to %.2f°C and %.2fK\n", fahrenheit, celsius, kelvin);
            break;

        case 3:
            printf("Enter temperature in Kelvin: ");
            scanf("%f", &kelvin);
            celsius = kelvin - 273.15;
            fahrenheit = (kelvin - 273.15) * 9/5 + 32;
            printf("%.2fK is equal to %.2f°C and %.2f°F\n", kelvin, celsius, fahrenheit);
            break;

        default:
            printf("Invalid option chosen.\n");
    }

    return 0;
}