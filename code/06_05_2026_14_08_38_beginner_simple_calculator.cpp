#include <iostream>
#include <string>

using namespace std;

int main() {
    string operation;
    double num1, num2, result;

    cout << "Simple Calculator" << endl;
    cout << "Enter a number: ";
    cin >> num1;
    cout << "Enter an operation (+, -, *, /): ";
    cin >> operation;
    cout << "Enter another number: ";
    cin >> num2;

    switch (operation[0]) {
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
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                cout << "Error: Division by zero!" << endl;
                return 1;
            }
            break;
        default:
            cout << "Error: Invalid operation!" << endl;
            return 1;
    }

    cout << "Result: " << result << endl;

    return 0;
}