# Calculator Program
import re

def calculate(expression):
    # Remove any whitespace from the expression
    expression = expression.replace(" ", "")

    # Check if the expression contains an operator
    if re.search("[+*^-]", expression):
        # Split the expression into two numbers and an operator
        nums = list(map(int, re.split("([+*^-])", expression)))
        op = expression[expression.index(nums[1])]

        # Perform the calculation based on the operator
        if op == "+":
            return nums[0] + nums[1]
        elif op == "-":
            return nums[0] - nums[1]
        elif op == "*":
            return nums[0] * nums[1]
        elif op == "/":
            if nums[1] != 0:
                return nums[0] / nums[1]

    # If no operator is found, the expression must be a single number
    else:
        return int(expression)

if __name__ == '__main__':
    expression = input("Enter a math expression: ")
    result = calculate(expression)
    print("The result is:", result)