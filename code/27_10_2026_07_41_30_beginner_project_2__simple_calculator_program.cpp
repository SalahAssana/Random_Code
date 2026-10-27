#include <iostream>
#include <cctype>

using namespace std;

int main() {
    double num1, num2;
    char operation;

    // Ask for first number
    cout << "Enter the first number: ";
    cin >> num1;

    // Ask for operation
    cout << "Enter operator (+, -, *, /): ";
    cin >> operation;

    // Check if entered operator is valid
    while (!(operation == '+' || operation == '-' || operation == '*' || operation == '/')) {
        cout << "Invalid operator. Enter a valid operator (+, -, *, /): ";
        cin >> operation;
    }

    // Ask for second number
    cout << "Enter the second number: ";
    cin >> num2;

    // Perform operation based on entered operator
    double result = 0;
    switch (operation) {
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
            if (num2 != 0)
                result = num1 / num2;
            else
                cout << "Error! Division by zero is not allowed.";
            break;
    }

    // Display the result
    cout << "The result is: " << result << endl;

    return 0;
}