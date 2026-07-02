#include <stdio.h>

int main() {
    float num1, num2;
    char operation;

    printf("Simple Calculator Program\n");
    printf("Enter first number: ");
    scanf("%f", &num1);
    printf("Enter operation (+, -, *, /): ");
    scanf(" %c", &operation);
    printf("Enter second number: ");
    scanf("%f", &num2);

    switch(operation) {
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
            if(num2 != 0) {
                printf("Result: %.2f\n", num1 / num2);
            } else {
                printf("Error! Division by zero is not allowed.\n");
            }
            break;
        default:
            printf("Invalid operation. Please try again.\n");
    }

    return 0;
}