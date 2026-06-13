#include <stdio.h>
#include <stdlib.h>

int main() {
    int num1, num2, choice;
    char operation;

    printf("Simple Calculator Program\n");
    printf("-------------------------------\n");

    while(1) {
        printf("Enter first number: ");
        scanf("%d", &num1);

        printf("Enter operation (+, -, *, /): ");
        scanf(" %c", &operation);

        printf("Enter second number: ");
        scanf("%d", &num2);

        switch(operation) {
            case '+':
                printf("Result: %d\n", num1 + num2);
                break;
            case '-':
                if(num2 > num1) {
                    printf("Error! Subtraction is not allowed.\n");
                } else {
                    printf("Result: %d\n", num1 - num2);
                }
                break;
            case '*':
                printf("Result: %d\n", num1 * num2);
                break;
            case '/':
                if(num2 == 0) {
                    printf("Error! Division by zero is not allowed.\n");
                } else {
                    printf("Result: %f\n", (float)num1 / num2);
                }
                break;
            default:
                printf("Invalid operation. Please try again.\n");
        }

        char cont;
        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &cont);

        if(cont == 'n') {
            break;
        }
    }

    return 0;
}