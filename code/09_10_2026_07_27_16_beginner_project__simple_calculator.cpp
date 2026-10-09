#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Function to evaluate simple mathematical expressions
double calculate(string expression) {
    // Check for basic arithmetic operations
    if (expression.find('+') != string::npos)
        return stod(expression.substr(0, expression.find('+'))) + stod(expression.substr(expression.find('+') + 1));
    else if (expression.find('-') != string::npos)
        return stod(expression.substr(0, expression.find('-'))) - stod(expression.substr(expression.find('-') + 1));
    else if (expression.find('*') != string::npos)
        return stod(expression.substr(0, expression.find('*'))) * stod(expression.substr(expression.find('*') + 1));
    else if (expression.find('/') != string::npos) {
        double numerator = stod(expression.substr(0, expression.find('/')));
        double denominator = stod(expression.substr(expression.find('/') + 1));
        return numerator / denominator;
    }
    // Check for power operation
    else if (expression.find('**') != string::npos)
        return pow(stod(expression.substr(0, expression.find('**'))), stod(expression.substr(expression.find('**') + 2)));
    // If no operator is found, return the input number
    else
        return stod(expression);
}

int main() {
    string expression;
    
    cout << "Enter a mathematical expression: ";
    getline(cin, expression);

    double result = calculate(expression);
    cout << "Result: " << result << endl;

    return 0;
}