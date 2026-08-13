# Calculator Program
def add(x, y):
    # Add two numbers
    return x + y

def subtract(x, y):
    # Subtract one number from another
    return x - y

def multiply(x, y):
    # Multiply two numbers
    return x * y

def divide(x, y):
    # Divide one number by another
    if y == 0:
        return "Error: Division by zero!"
    else:
        return x / y

def calculator():
    print("Welcome to the Calculator Program!")
    num1 = float(input("Enter the first number: "))
    op = input("Enter an operator (+, -, *, /): ")
    num2 = float(input("Enter the second number: "))

    if op == "+":
        result = add(num1, num2)
    elif op == "-":
        result = subtract(num1, num2)
    elif op == "*":
        result = multiply(num1, num2)
    elif op == "/":
        result = divide(num1, num2)
    else:
        result = "Error: Invalid operator!"

    print(f"Result: {result}")

if __name__ == '__main__':
    calculator()