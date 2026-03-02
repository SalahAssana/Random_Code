#include <stdio.h>

int main() {
    int num1, num2, choice;
    float result;

    printf("Simple Calculator\n");
    printf("-----------------\n");

    while(1) {
        printf("Enter your choice:\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Quit\n");

        scanf("%d", &choice);

        if(choice == 5) {
            break;
        }

        printf("Enter first number: ");
        scanf("%d", &num1);
        printf("Enter second number: ");
        scanf("%d", &num2);

        switch(choice) {
            case 1:
                result = num1 + num2;
                printf("Result: %.2f\n", result);
                break;
            case 2:
                result = num1 - num2;
                printf("Result: %.2f\n", result);
                break;
            case 3:
                result = num1 * num2;
                printf("Result: %.2f\n", result);
                break;
            case 4:
                if(num2 == 0) {
                    printf("Error! Division by zero is not allowed.\n");
                } else {
                    result = (float)num1 / num2;
                    printf("Result: %.2f\n", result);
                }
                break;
        }
    }

    return 0;
}