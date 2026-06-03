# Simple Calculator Program
# BEGINNER Complexity Level

def add(x, y):
    # Add two numbers
    return x + y

def subtract(x, y):
    # Subtract y from x
    return x - y

def multiply(x, y):
    # Multiply two numbers
    return x * y

def divide(x, y):
    # Divide x by y
    if y == 0:
        return "Error: Division by zero is not allowed"
    else:
        return x / y

if __name__ == '__main__':
    print("Simple Calculator")
    while True:
        user_input = input("Enter operation (+, -, *, /), or 'q' to quit: ")
        
        if user_input.lower() == 'q':
            break
        
        try:
            num1 = float(input("Enter first number: "))
            num2 = float(input("Enter second number: "))

            if user_input == "+":
                print(num1, "+", num2, "=", add(num1, num2))
            elif user_input == "-":
                print(num1, "-", num2, "=", subtract(num1, num2))
            elif user_input == "*":
                print(num1, "*", num2, "=", multiply(num1, num2))
            elif user_input == "/":
                print(num1, "/", num2, "=", divide(num1, num2))
            else:
                print("Invalid operation. Please try again.")
        except ValueError:
            print("Invalid input. Please enter numbers and operators correctly.")