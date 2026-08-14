#include <stdio.h>

int main() {
    int num1, num2, choice;
    float result;

    // Display menu
    printf("Simple Calculator Program\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Get two numbers from user
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);

    switch (choice) {
        case 1:
            result = num1 + num2;
            break;
        case 2:
            result = num1 - num2;
            break;
        case 3:
            result = num1 * num2;
            break;
        case 4:
            if (num2 != 0) {
                result = (float)num1 / num2;
            } else {
                printf("Error! Division by zero is not allowed.\n");
                return 1; // Exit program
            }
            break;
        default:
            printf("Error! Invalid choice. Please try again.\n");
            return 1; // Exit program
    }

    // Display result
    printf("Result: %f\n", result);

    return 0;
}