#include <stdio.h>

int main() {
    int num1, num2;
    char operation;

    // Ask user for two numbers
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);

    // Ask user for an operator (+, -, *, /)
    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &operation);

    int result = 0;

    switch(operation) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                printf("Error: Division by zero!\n");
                return 1;
            }
            break;
        default:
            printf("Error: Invalid operator!\n");
            return 1;
    }

    // Print the result
    printf("Result: %d\n", result);

    return 0;
}