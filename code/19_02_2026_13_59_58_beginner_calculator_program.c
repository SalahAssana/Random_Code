#include <stdio.h>

int main() {
    int num1, num2;
    char op;

    // Prompt user for two numbers
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &op);

    printf("Enter second number: ");
    scanf("%d", &num2);

    int result = 0;

    switch(op) {
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
                printf("Error! Division by zero is not allowed.\n");
            break;
        default:
            printf("Invalid operator. Please try again.\n");
    }

    printf("Result: %d\n", result);

    return 0;
}