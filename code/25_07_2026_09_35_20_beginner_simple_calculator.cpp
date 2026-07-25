#include <iostream>
using namespace std;

int main() {
    int num1, num2;
    char op;

    // Ask for two numbers
    cout << "Enter first number: ";
    cin >> num1;

    cout << "Enter operator (+, -, *, /): ";
    cin >> op;

    cout << "Enter second number: ";
    cin >> num2;

    int result = 0;
    switch (op) {
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
            cout << "Error! Invalid operator. Please enter +, -, * or /." << endl;
    }

    if (result != 0)
        cout << "Result: " << result << endl;

    return 0;
}