# Simple Calculator
# Complexity Level: BEGINNER

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
    """Divide two numbers"""
    if y == 0:
        print("Error! Division by zero is not allowed.")
        return None
    return x / y

def calculator():
    print("Simple Calculator")
    print("------------------")

    num1 = float(input("Enter the first number: "))
    operator = input("Enter the operator (+, -, *, /): ")
    
    if operator == "+":
        num2 = float(input("Enter the second number: "))
        result = add(num1, num2)
    elif operator == "-":
        num2 = float(input("Enter the second number: "))
        result = subtract(num1, num2)
    elif operator == "*":
        num2 = float(input("Enter the second number: "))
        result = multiply(num1, num2)
    elif operator == "/":
        num2 = float(input("Enter the second number: "))
        result = divide(num1, num2)
    else:
        print("Invalid operator. Please try again.")
        return

    print(f"Result: {result}")

if __name__ == '__main__':
    calculator()