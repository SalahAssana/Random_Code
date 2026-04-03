#include <stdio.h>

int main() {
    int num1, num2;
    char operation;

    // Ask user for two numbers and an operation
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);
    printf("Enter operation (+, -, *, /): ");
    scanf(" %c", &operation);

    // Perform the operation based on user's choice
    if(operation == '+') {
        printf("Result = %d\n", num1 + num2);
    } else if(operation == '-') {
        printf("Result = %d\n", num1 - num2);
    } else if(operation == '*') {
        printf("Result = %d\n", num1 * num2);
    } else if(operation == '/') {
        // Check for division by zero
        if(num2 != 0) {
            printf("Result = %.2f\n", (float)num1 / num2);
        } else {
            printf("Error! Division by zero is not allowed.\n");
        }
    } else {
        printf("Invalid operation. Please enter one of the following: +, -, *, /\n");
    }

    return 0;
}