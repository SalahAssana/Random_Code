#include <iostream>
using namespace std;

int main() {
    int num1, num2;
    char operation;

    // Ask user for two numbers
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter second number: ";
    cin >> num2;

    // Ask user for operation (+, -, *, /)
    cout << "Enter operation (+, -, *, /): ";
    cin >> operation;

    int result = 0;

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
                cout << "Error! Division by zero is not allowed." << endl;
            break;
        default:
            cout << "Error! Invalid operation. Please try again." << endl;
            break;
    }

    // Display the result
    if (result != 0)
        cout << "Result: " << num1 << " " << operation << " " << num2 << " = " << result << endl;

    return 0;
}