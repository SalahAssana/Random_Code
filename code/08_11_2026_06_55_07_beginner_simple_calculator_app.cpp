#include <iostream>
#include <string>

using namespace std;

int main() {
    double num1, num2;
    char operation;

    cout << "Simple Calculator App" << endl;
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter operator (+, -, *, /): ";
    cin >> operation;
    cout << "Enter second number: ";
    cin >> num2;

    if (operation == '+') {
        cout << "Result: " << num1 + num2 << endl;
    } else if (operation == '-') {
        cout << "Result: " << num1 - num2 << endl;
    } else if (operation == '*') {
        cout << "Result: " << num1 * num2 << endl;
    } else if (operation == '/') {
        if (num2 != 0) {
            cout << "Result: " << num1 / num2 << endl;
        } else {
            cout << "Error! Division by zero." << endl;
        }
    } else {
        cout << "Error! Invalid operator." << endl;
    }

    return 0;
}