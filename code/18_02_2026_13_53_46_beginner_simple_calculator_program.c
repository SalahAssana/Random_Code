#include <stdio.h>

int main() {
    int num1, num2;
    char operation;

    printf("Simple Calculator Program\n");
    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter operation (+, -, *, /): ");
    scanf(" %c", &operation);

    printf("Enter second number: ");
    scanf("%d", &num2);

    switch(operation) {
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
            if(num2 != 0) {
                printf("Result = %.2f\n", (double)num1 / num2);
            } else {
                printf("Error! Division by zero is not allowed.\n");
            }
            break;
        default:
            printf("Error! Invalid operation. Try again.\n");
    }

    return 0;
}