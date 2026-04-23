# Simple Calculator in Python

def get_user_input():
    num1 = float(input("Enter first number: "))
    operator = input("Enter operator (+, -, *, /): ")
    num2 = float(input("Enter second number: "))

    return num1, operator, num2

def perform_operation(num1, operator, num2):
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
            print("Error: Division by zero is not allowed.")
            return None
    else:
        print("Error: Invalid operator. Please enter +, -, or *.")
        return None

    return result

def main():
    num1, operator, num2 = get_user_input()
    result = perform_operation(num1, operator, num2)

    if result is not None:
        print(f"Result: {result}")

if __name__ == '__main__':
    main()