#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to evaluate math expression
double eval(char* exp) {
    // Create a stack for operators and operands
    double* stack = (double*)malloc(sizeof(double) * 100);
    int top = -1;

    // Initialize the result variable
    double res = 0.0;
    int sign = 1; // Sign of the expression (1 if positive, -1 if negative)

    // Parse the expression
    char* token = strtok(exp, " ");
    while(token) {
        // Check for operators and operands
        if(strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || 
           strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
            // Pop the top operand from the stack and apply the operator
            double op1 = stack[top--];
            double op2 = res;
            res = 0.0;

            if(strcmp(token, "+") == 0)
                res = op1 + op2 * sign;
            else if(strcmp(token, "-") == 0)
                res = op1 - op2 * sign;
            else if(strcmp(token, "*") == 0)
                res = op1 * op2;
            else
                res = op1 / op2;

            // Push the result back onto the stack with the correct sign
            stack[++top] = res;
        } 
        else {
            // Convert token to double and push it onto the stack
            double val = atof(token);
            if(sign == -1)
                res -= val;
            else
                res += val;

            sign = 1; // Reset the sign for next number
        }

        token = strtok(NULL, " ");
    }

    // Pop the final result from the stack and return it
    res = stack[top--];
    free(stack);
    return res;
}

int main() {
    char exp[100];
    printf("Enter a math expression: ");
    fgets(exp, sizeof(exp), stdin);
    exp[strlen(exp) - 1] = '\0'; // Remove the newline character

    double result = eval(exp);
    printf("Result: %f\n", result);

    return 0;
}