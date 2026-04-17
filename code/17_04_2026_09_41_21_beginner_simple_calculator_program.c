#include <stdio.h>

int main() {
    int num1, num2;
    char operation;

    // Ask for two numbers from user
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);

    // Ask for the operation to be performed
    printf("Enter operation (+, -, *, /): ");
    scanf(" %c", &operation);

    // Perform the operation based on user input
    if(operation == '+') {
        printf("Result = %d\n", num1 + num2);
    } else if(operation == '-') {
        printf("Result = %d\n", num1 - num2);
    } else if(operation == '*') {
        printf("Result = %d\n", num1 * num2);
    } else if(operation == '/') {
        if(num2 != 0) {
            printf("Result = %.2f\n", (float)num1 / num2);
        } else {
            printf("Error! Division by zero is not allowed.\n");
        }
    } else {
        printf("Invalid operation. Please enter a valid operator (+, -, *, /).\n");
    }

    return 0;
}