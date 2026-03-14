#include <iostream>
#include <cctype>
#include <cmath>
#include <string>

using namespace std;

// Function to evaluate mathematical expression
double calculate(string expression) {
    double result = 0;
    char operation = '+';
    int num1 = 0, num2 = 0;

    for (int i = 0; i < expression.length(); i++) {
        if (isdigit(expression[i])) {
            num1 = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                num1 = num1 * 10 + (expression[i] - '0');
                i++;
            }
        } else if (expression[i] == '.') {
            int decimalPosition = i;
            while (i < expression.length() && isdigit(expression[i])) {
                num1 = num1 * 10 + (expression[i] - '0');
                i++;
            }
            result += (num1 / pow(10, i - decimalPosition));
        } else if (expression[i] == '(') {
            int balance = 1;
            for (++i; i < expression.length(); i++) {
                if (expression[i] == '(')
                    balance++;
                else if (expression[i] == ')')
                    balance--;
                if (balance == 0)
                    break;
            }
        } else if (expression[i] == '+' || expression[i] == '-' ||
                   expression[i] == '*' || expression[i] == '/') {
            operation = expression[i];
            num2 = 0;
        }

        // Perform the operation
        switch (operation) {
            case '+':
                result += num1;
                break;
            case '-':
                result -= num1;
                break;
            case '*':
                result *= num1;
                break;
            case '/':
                if (num1 != 0)
                    result /= num1;
                else
                    cout << "Error: Division by zero!" << endl;
        }
    }

    return result;
}

int main() {
    string expression;

    // Get mathematical expression from user
    cout << "Enter a mathematical expression (e.g., 2+3*4): ";
    getline(cin, expression);

    double result = calculate(expression);
    cout << "Result: " << result << endl;

    return 0;
}