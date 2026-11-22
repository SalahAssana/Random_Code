#include <stdio.h>

int main() {
    int num1, num2;
    char op;

    // Ask user for two numbers and an operation
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);
    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &op);

    // Perform the operation based on the user's choice
    switch(op) {
        case '+':
            printf("Result = %d\n", num1 + num2);
            break;
        case '-':
            printf("Result = %d\n", num1 - num2);
            break;
        case '*':
            printf("Result = %d\n", num1 * num2);
            break;
        case '/':
            if(num2 != 0)
                printf("Result = %.2f\n", (float)num1 / num2);
            else
                printf("Error! Division by zero is not allowed.\n");
            break;
        default:
            printf("Invalid operator. Please enter +, -, * or /.");
    }

    return 0;
}