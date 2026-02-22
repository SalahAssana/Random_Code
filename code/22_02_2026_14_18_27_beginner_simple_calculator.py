# Simple Calculator in Python

def add(x, y):
    return x + y

def subtract(x, y):
    return x - y

def multiply(x, y):
    return x * y

def divide(x, y):
    if y == 0:
        return "Error: Division by zero is not allowed"
    else:
        return x / y

def calculator():
    print("Simple Calculator")
    while True:
        num1 = float(input("Enter first number: "))
        op = input("Enter operator (+, -, *, /): ")
        if op == "+":
            result = add(num1, float(input("Enter second number: ")))
        elif op == "-":
            result = subtract(num1, float(input("Enter second number: ")))
        elif op == "*":
            result = multiply(num1, float(input("Enter second number: ")))
        elif op == "/":
            result = divide(num1, float(input("Enter second number: ")))
        else:
            print("Invalid operator. Please try again.")
        print(f"Result: {result}")
        cont = input("Do you want to continue? (yes/no): ")
        if cont.lower() != "yes":
            break

if __name__ == '__main__':
    calculator()