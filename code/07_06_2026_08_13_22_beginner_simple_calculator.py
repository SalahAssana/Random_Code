# Simple Calculator
# A simple calculator that performs basic arithmetic operations.

def add(x, y):
    """Add two numbers"""
    return x + y

def subtract(x, y):
    """Subtract one number from another"""
    return x - y

def multiply(x, y):
    """Multiply two numbers"""
    return x * y

def divide(x, y):
    """Divide one number by another"""
    if y == 0:
        return "Error: Division by zero is not allowed"
    else:
        return x / y

if __name__ == '__main__':
    num1 = float(input("Enter the first number: "))
    op = input("Enter operator (+, -, *, /): ")
    num2 = float(input("Enter the second number: "))

    if op == "+":
        print("Result:", add(num1, num2))
    elif op == "-":
        print("Result:", subtract(num1, num2))
    elif op == "*":
        print("Result:", multiply(num1, num2))
    elif op == "/":
        print("Result:", divide(num1, num2))
    else:
        print("Invalid operator. Please try again!")