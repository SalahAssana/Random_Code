#include <iostream>
using namespace std;

int main() {
    int num1, num2;
    char operation;

    cout << "Simple Calculator" << endl;
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter operation (+, -, *, /): ";
    cin >> operation;
    cout << "Enter second number: ";
    cin >> num2;

    int result = 0;

    switch(operation) {
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
            cout << "Error! Invalid operation. Please enter +, -, * or /." << endl;
    }

    if (result != 0)
        cout << "Result: " << result << endl;

    return 0;
}