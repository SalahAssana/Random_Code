#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

int evaluate(char *expression) {
    // Create a temporary buffer to store the result
    char result[MAX_LENGTH];
    int len = strlen(expression);

    for (int i = 0; i < len; i++) {
        if (isdigit(expression[i])) {
            // Check for negative numbers
            if (i == 0 && expression[i] == '-') {
                strcat(result, "-");
                i++;
            }
            // Add digits to the result string
            strcat(result, &expression[i]);
        } else if (strchr("+-*/.", expression[i]) != NULL) {
            strcat(result, &expression[i]);
        }
    }

    return atoi(result);
}

int main() {
    char expression[MAX_LENGTH];
    printf("Enter a mathematical expression: ");
    fgets(expression, MAX_LENGTH, stdin);

    int result = evaluate(expression);
    printf("Result: %d\n", result);

    return 0;
}