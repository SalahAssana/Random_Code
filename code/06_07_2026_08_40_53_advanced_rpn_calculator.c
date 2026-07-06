#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct to represent a stack node
typedef struct {
    double value;
    int isOperator;
} StackNode;

// Define a function to create a new stack node
StackNode* createStackNode(double value, int isOperator) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->value = value;
    newNode->isOperator = isOperator;
    return newNode;
}

// Define a struct to represent the calculator
typedef struct {
    StackNode** stack;
    int stackSize;
    int topOfStack;
} Calculator;

// Define a function to create a new calculator
Calculator* createCalculator(int initialStackSize) {
    Calculator* calc = (Calculator*)malloc(sizeof(Calculator));
    calc->stack = (StackNode**)malloc(initialStackSize * sizeof(StackNode*));
    calc->stackSize = initialStackSize;
    calc->topOfStack = -1;
    return calc;
}

// Define a function to free the calculator
void freeCalculator(Calculator* calc) {
    for(int i = 0; i <= calc->topOfStack; i++) {
        free(calc->stack[i]);
    }
    free(calc->stack);
    free(calc);
}

// Define a function to evaluate an RPN expression
double evaluateRPN(char** tokens, int numTokens, Calculator* calc) {
    for(int i = 0; i < numTokens; i++) {
        if(strcmp(tokens[i], "+") == 0 || strcmp(tokens[i], "-") == 0 || 
           strcmp(tokens[i], "*") == 0 || strcmp(tokens[i], "/") == 0) {
            // Pop two operands from the stack
            StackNode* operand2 = calc->stack[calc->topOfStack--];
            StackNode* operand1 = calc->stack[calc->topOfStack--];

            // Perform the operation
            double result;
            if(strcmp(tokens[i], "+") == 0) {
                result = operand1->value + operand2->value;
            } else if(strcmp(tokens[i], "-") == 0) {
                result = operand1->value - operand2->value;
            } else if(strcmp(tokens[i], "*") == 0) {
                result = operand1->value * operand2->value;
            } else {
                result = operand1->value / operand2->value;
            }

            // Push the result onto the stack
            calc->stack[++calc->topOfStack] = createStackNode(result, 0);
        } else {
            // Push the token value onto the stack
            calc->stack[++calc->topOfStack] = createStackNode atof(tokens[i]), 0;
        }
    }

    // Return the final result from the stack
    return calc->stack[0]->value;
}

int main() {
    Calculator* calc = createCalculator(10);
    
    char** tokens = (char**)malloc(sizeof(char*) * 5);
    strcpy(tokens[0], "2");
    strcpy(tokens[1], "3");
    strcpy(tokens[2], "+");
    strcpy(tokens[3], "4");
    strcpy(tokens[4], "*");

    double result = evaluateRPN(tokens, 5, calc);

    printf("Result: %f\n", result);

    freeCalculator(calc);
    return 0;
}