# Calculator Program
# A simple program that takes user input and performs basic arithmetic operations.

def calculate():
    # Initialize variables for calculation
    num1 = float(input("Enter first number: "))
    op = input("Enter operator (+, -, *, /): ")
    num2 = float(input("Enter second number: "))

    if op == "+":
        print(f"{num1} + {num2} = {num1 + num2}")
    elif op == "-":
        print(f"{num1} - {num2} = {num1 - num2}")
    elif op == "*":
        print(f"{num1} * {num2} = {num1 * num2}")
    elif op == "/":
        if num2 != 0:
            print(f"{num1} / {num2} = {num1 / num2}")
        else:
            print("Error: Division by zero!")
    else:
        print("Invalid operator! Try again.")

if __name__ == '__main__':
    calculate()