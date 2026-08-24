#include <iostream>
#include <string>
#include <cctype>

// Function to evaluate mathematical expressions
double calculate(const std::string& expression) {
    double result = 0;
    int sign = 1; // 1 for positive, -1 for negative
    int numStart = 0;

    for (int i = 0; i < expression.size(); ++i) {
        if (std::isdigit(expression[i])) {
            numStart = i;
            while (i < expression.size() && std::isdigit(expression[i]))
                ++i;
            result += sign * (expression.substr(numStart, i - numStart) - '0');
        } else if (expression[i] == '.') {
            int dotPos = i;
            while (i < expression.size() && std::isdigit(expression[i]))
                ++i;
            result += '.'s[dotPos - numStart];
        } else if (std::isalpha(expression[i])) {
            // Ignore letters
        } else if (expression[i] == '+') {
            sign = 1;
        } else if (expression[i] == '-') {
            sign = -1;
        }
    }

    return result;
}

int main() {
    std::cout << "Enter a mathematical expression: ";
    std::string expression;
    std::cin >> expression;

    double result = calculate(expression);
    std::cout << "Result: " << result << std::endl;

    return 0;
}