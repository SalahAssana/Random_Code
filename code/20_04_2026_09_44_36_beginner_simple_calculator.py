# Simple Calculator Program in Python

def add(x, y):
    """Add two numbers"""
    return x + y

def subtract(x, y):
    """Subtract two numbers"""
    return x - y

def multiply(x, y):
    """Multiply two numbers"""
    return x * y

def divide(x, y):
    """Divide two numbers (if y is not zero)"""
    if y == 0:
        return "Error: Division by zero"
    else:
        return x / y

def calculator():
    print("Simple Calculator")
    while True:
        num1 = float(input("Enter first number: "))
        op = input("Enter operator (+, -, *, /): ")
        num2 = float(input("Enter second number: "))

        if op == "+":
            result = add(num1, num2)
        elif op == "-":
            result = subtract(num1, num2)
        elif op == "*":
            result = multiply(num1, num2)
        elif op == "/":
            result = divide(num1, num2)
        else:
            print("Invalid operator. Try again!")
            continue

        print(f"{num1} {op} {num2} = {result}")

if __name__ == '__main__':
    calculator()