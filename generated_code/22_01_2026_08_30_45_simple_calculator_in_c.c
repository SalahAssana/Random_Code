#include <stdio.h>
#include <stdlib.h>

// Function to get operator from user
char getOperator() {
    char op;
    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &op);
    return op;
}

// Function to perform calculation based on operator
float performCalculation(float num1, float num2, char op) {
    switch (op) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 == 0) {
                printf("Error! Division by zero is not allowed.\n");
                exit(1);
            }
            return num1 / num2;
        default:
            printf("Error! Invalid operator. Please enter +, -, *, or /. \n");
            exit(1);
    }
}

// Main function to get input from user and perform calculation
int main() {
    float num1, num2;
    char op;

    // Get first number from user
    printf("Enter first number: ");
    scanf("%f", &num1);

    // Get operator from user
    op = getOperator();

    // Get second number from user
    printf("Enter second number: ");
    scanf("%f", &num2);

    // Perform calculation and print result
    float result = performCalculation(num1, num2, op);
    printf("\nResult: %.2f\n", result);

    return 0;
}