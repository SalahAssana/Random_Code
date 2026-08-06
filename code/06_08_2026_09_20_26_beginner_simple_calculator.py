# Simple Calculator
# A beginner-friendly program that implements basic arithmetic operations

def calculate():
    print("Simple Calculator")
    print("-----------------")

    num1 = float(input("Enter first number: "))
    operator = input("Enter operator (+, -, *, /): ")
    num2 = float(input("Enter second number: "))

    if operator == "+":
        result = num1 + num2
    elif operator == "-":
        result = num1 - num2
    elif operator == "*":
        result = num1 * num2
    elif operator == "/":
        if num2 != 0:
            result = num1 / num2
        else:
            print("Error! Division by zero is not allowed.")
            return
    else:
        print("Invalid operator. Please try again.")
        return

    print(f"Result: {num1} {operator} {num2} = {result}")

if __name__ == '__main__':
    calculate()