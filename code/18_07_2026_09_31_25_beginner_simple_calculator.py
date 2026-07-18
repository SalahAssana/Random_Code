# Simple Calculator Program
# Author: [Your Name]
# Complexity Level: BEGINNER

# Import necessary modules
import math

def add(x, y):
    # Add two numbers and return the result
    return x + y

def subtract(x, y):
    # Subtract two numbers and return the result
    return x - y

def multiply(x, y):
    # Multiply two numbers and return the result
    return x * y

def divide(x, y):
    # Divide two numbers and return the result
    if y == 0:
        return "Error: Division by zero is not allowed"
    else:
        return x / y

def calculator():
    print("Simple Calculator Program")
    while True:
        print("\nSelect an operation:")
        print("1. Addition")
        print("2. Subtraction")
        print("3. Multiplication")
        print("4. Division")
        print("5. Exit")

        choice = input("Enter your choice (1/2/3/4/5): ")

        if choice in ('1', '2', '3', '4'):
            num1 = float(input("Enter first number: "))
            num2 = float(input("Enter second number: "))

            if choice == '1':
                print("\nResult:", add(num1, num2))
            elif choice == '2':
                print("\nResult:", subtract(num1, num2))
            elif choice == '3':
                print("\nResult:", multiply(num1, num2))
            elif choice == '4':
                print("\nResult:", divide(num1, num2))

        elif choice == '5':
            print("\nExiting the program...")
            break
        else:
            print("\nInvalid choice. Please choose again.")

if __name__ == '__main__':
    calculator()