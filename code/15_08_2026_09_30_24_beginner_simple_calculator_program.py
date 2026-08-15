# Simple Calculator Program
# BEGINNER complexity project

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
    print("Simple Calculator Program")
    print("-------------------------")

    while True:
        user_input = input("Enter operation (+, -, *, /) or 'q' to quit: ")

        if user_input == 'q':
            break
        elif user_input in ('+', '-', '*', '/'):
            num1 = float(input("Enter first number: "))
            num2 = float(input("Enter second number: "))

            if user_input == '+':
                result = add(num1, num2)
            elif user_input == '-':
                result = subtract(num1, num2)
            elif user_input == '*':
                result = multiply(num1, num2)
            elif user_input == '/':
                result = divide(num1, num2)

            print("Result: ", result)
        else:
            print("Invalid input. Please try again.")

if __name__ == '__main__':
    calculator()