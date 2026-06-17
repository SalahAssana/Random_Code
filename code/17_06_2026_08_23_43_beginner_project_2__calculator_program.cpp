#include <iostream>
using namespace std;

int main() {
    double num1, num2;
    char operation;

    // Ask user for two numbers and an operator
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter second number: ";
    cin >> num2;
    cout << "Enter an operator (+, -, *, /): ";
    cin >> operation;

    // Perform the operation based on the user's choice
    if (operation == '+') {
        cout << "Result: " << num1 + num2 << endl;
    } else if (operation == '-') {
        cout << "Result: " << num1 - num2 << endl;
    } else if (operation == '*') {
        cout << "Result: " << num1 * num2 << endl;
    } else if (operation == '/') {
        // Check for division by zero
        if (num2 != 0) {
            cout << "Result: " << num1 / num2 << endl;
        } else {
            cout << "Error: Division by zero is not allowed!" << endl;
        }
    } else {
        cout << "Error: Invalid operator. Please enter +, -, * or /." << endl;
    }

    return 0;
}