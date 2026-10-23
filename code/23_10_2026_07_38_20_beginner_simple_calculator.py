# Simple Calculator
# Author: [Your Name]

def add(x, y):
    """
    Adds two numbers together.
    
    Parameters:
        x (int): The first number.
        y (int): The second number.
        
    Returns:
        int: The sum of the two numbers.
    """
    return x + y

def subtract(x, y):
    """
    Subtracts the second number from the first.
    
    Parameters:
        x (int): The first number.
        y (int): The second number.
        
    Returns:
        int: The difference between the two numbers.
    """
    return x - y

def multiply(x, y):
    """
    Multiplies two numbers together.
    
    Parameters:
        x (int): The first number.
        y (int): The second number.
        
    Returns:
        int: The product of the two numbers.
    """
    return x * y

def divide(x, y):
    """
    Divides the first number by the second.
    
    Parameters:
        x (int): The dividend.
        y (int): The divisor.
        
    Returns:
        float: The quotient.
    """
    if y == 0:
        return "Error: Division by zero is not allowed."
    else:
        return x / y

def main():
    print("Simple Calculator")
    print("-----------------")

    num1 = int(input("Enter the first number: "))
    op = input("Enter an operation (+, -, *, /): ")
    num2 = int(input("Enter the second number: "))

    if op == "+":
        result = add(num1, num2)
    elif op == "-":
        result = subtract(num1, num2)
    elif op == "*":
        result = multiply(num1, num2)
    elif op == "/":
        result = divide(num1, num2)
    else:
        print("Error: Invalid operation. Please try again.")
        return

    print(f"Result: {result}")

if __name__ == '__main__':
    main()