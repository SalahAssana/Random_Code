#include <stdio.h>

int main() {
    int temp;
    int humidity;
    int windSpeed;

    printf("Enter temperature (0-100): ");
    scanf("%d", &temp);

    printf("Enter humidity (0-100): ");
    scanf("%d", &humidity);

    printf("Enter wind speed (0-50): ");
    scanf("%d", &windSpeed);

    if (temp > 70 && humidity < 40) {
        printf("Sunny\n");
    } else if (temp < 60 || humidity > 80) {
        printf("Rainy\n");
    } else if (windSpeed > 30) {
        printf("Windy\n");
    } else {
        printf("Partly Cloudy\n");
    }

    return 0;
}