#include <stdio.h>

int main() {
    int choice;
    double temp;

    // Ask user for conversion type
    printf("Enter 1 to convert Celsius to Fahrenheit.\n");
    printf("Enter 2 to convert Fahrenheit to Celsius.\n");
    scanf("%d", &choice);

    if (choice == 1) {
        // Get temperature in Celsius
        printf("Enter temperature in Celsius: ");
        scanf("%lf", &temp);
        // Convert Celsius to Fahrenheit
        temp = (temp * 9 / 5) + 32;
        printf("%.2f degrees Celsius is %.2f degrees Fahrenheit.\n", temp, temp);
    } else if (choice == 2) {
        // Get temperature in Fahrenheit
        printf("Enter temperature in Fahrenheit: ");
        scanf("%lf", &temp);
        // Convert Fahrenheit to Celsius
        temp = (temp - 32) * 5 / 9;
        printf("%.2f degrees Fahrenheit is %.2f degrees Celsius.\n", temp, temp);
    } else {
        printf("Invalid choice. Please try again.");
    }

    return 0;
}