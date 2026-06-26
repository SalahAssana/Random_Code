# Calculator App
import re

def calculate(expression):
    # Remove any whitespace characters
    expression = expression.replace(" ", "")

    # Check if the expression is valid
    if not re.match("^[0-9+-*/.]+$", expression):
        return "Invalid input"

    try:
        result = eval(expression)
        return str(result)
    except Exception as e:
        return "Error: " + str(e)

if __name__ == '__main__':
    while True:
        expression = input("Enter a math expression (or 'q' to quit): ")
        if expression.lower() == 'q':
            break
        print(calculate(expression))