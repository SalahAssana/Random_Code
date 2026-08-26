#include <stdio.h>

int main() {
    float num1, num2;
    char op;

    printf("Simple Calculator\n");
    printf("Enter first number: ");
    scanf("%f", &num1);
    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &op);

    if(op == '+') {
        printf("Result: %.2f\n", num1 + num2);
    } else if(op == '-') {
        printf("Result: %.2f\n", num1 - num2);
    } else if(op == '*') {
        printf("Result: %.2f\n", num1 * num2);
    } else if(op == '/') {
        if(num2 != 0) {
            printf("Result: %.2f\n", num1 / num2);
        } else {
            printf("Error! Division by zero is not allowed.\n");
        }
    } else {
        printf("Invalid operator. Please enter one of the following: +, -, *, /\n");
    }

    return 0;
}