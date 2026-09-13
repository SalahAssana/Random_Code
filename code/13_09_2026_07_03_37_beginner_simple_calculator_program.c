#include <stdio.h>

int main() {
    char operation;
    float num1, num2;

    printf("Simple Calculator Program\n");
    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &operation);

    printf("Enter first number: ");
    scanf(" %f", &num1);

    printf("Enter second number: ");
    scanf(" %f", &num2);

    switch (operation) {
        case '+':
            printf("Result: %.2f\n", num1 + num2);
            break;
        case '-':
            printf("Result: %.2f\n", num1 - num2);
            break;
        case '*':
            printf("Result: %.2f\n", num1 * num2);
            break;
        case '/':
            if (num2 != 0) {
                printf("Result: %.2f\n", num1 / num2);
            } else {
                printf("Error! Division by zero is not allowed.\n");
            }
            break;
        default:
            printf("Invalid operator. Please try again.\n");
    }

    return 0;
}