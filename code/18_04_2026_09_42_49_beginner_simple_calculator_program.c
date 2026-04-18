#include <stdio.h>

int main() {
    int num1, num2;
    char operation;

    // Prompt user for input
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter operation (+, -, *, /): ");
    scanf(" %c", &operation);
    printf("Enter second number: ");
    scanf("%d", &num2);

    // Perform arithmetic operations
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
            if(num2 != 0)
                result = num1 / num2;
            else
                printf("Error: Division by zero is not allowed.\n");
            break;
        default:
            printf("Error: Invalid operation. Only +, -, * and / are supported.\n");
    }

    // Display the result
    printf("Result: %d\n", result);

    return 0;
}