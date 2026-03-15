#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to evaluate mathematical expressions
double calculate(string expression) {
    double result = 0;
    int sign = 1; // Sign of the number (1 for positive, -1 for negative)
    double num = 0; // Current number being processed

    for (char c : expression) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        } else if (c == '.') {
            result += sign * num;
            num = 0;
            sign = 1;
        } else if (c == '+' || c == '-') {
            result += sign * num;
            num = 0;
            sign = (c == '+') ? 1 : -1;
        }
    }

    // Add the last number
    result += sign * num;

    return result;
}

int main() {
    string expression;
    
    cout << "Enter a mathematical expression: ";
    getline(cin, expression);
    
    double result = calculate(expression);

    cout << "Result: " << result << endl;

    return 0;
}