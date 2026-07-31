#include <stdio.h>

int main() {
    int num1, num2;
    char operation;

    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &operation);

    printf("Enter second number: ");
    scanf("%d", &num2);

    if(operation == '+') {
        printf("Result: %d\n", num1 + num2);
    } else if(operation == '-') {
        printf("Result: %d\n", num1 - num2);
    } else if(operation == '*') {
        printf("Result: %d\n", num1 * num2);
    } else if(operation == '/') {
        if(num2 != 0) {
            printf("Result: %.2f\n", (float)num1 / num2);
        } else {
            printf("Error! Division by zero is not allowed.\n");
        }
    } else {
        printf("Invalid operation. Please enter +, -, * or /\n");
    }

    return 0;
}