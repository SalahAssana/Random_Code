# Calculator Program

def calculator():
    # Initialize variables
    result = 0
    operations = {"+": lambda x, y: x + y, 
                  "-": lambda x, y: x - y, 
                  "*": lambda x, y: x * y, 
                  "/": lambda x, y: x / y}

    while True:
        # Get user input
        num1 = float(input("Enter the first number: "))
        operation = input("Enter an operation (+, -, *, /): ")
        if operation not in operations:
            print("Invalid operation. Please try again.")
            continue

        num2 = float(input("Enter the second number: "))

        # Perform the operation
        result = operations[operation](num1, num2)

        print(f"Result: {result}")

if __name__ == '__main__':
    calculator()