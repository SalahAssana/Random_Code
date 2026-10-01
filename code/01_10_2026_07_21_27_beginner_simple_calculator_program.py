# Simple Calculator Program
def calculator():
    print("Simple Calculator")
    while True:
        print("1. Addition")
        print("2. Subtraction")
        print("3. Multiplication")
        print("4. Division")
        choice = input("Choose an operation (1/2/3/4) or 'q' to quit: ")
        
        if choice == 'q':
            break
        
        num1 = float(input("Enter first number: "))
        num2 = float(input("Enter second number: "))

        if choice == '1':
            print(f"{num1} + {num2} = {num1 + num2}")
        elif choice == '2':
            print(f"{num1} - {num2} = {num1 - num2}")
        elif choice == '3':
            print(f"{num1} * {num2} = {num1 * num2}")
        elif choice == '4':
            if num2 != 0:
                print(f"{num1} / {num2} = {num1 / num2}")
            else:
                print("Error! Division by zero is not allowed.")
        else:
            print("Invalid operation. Please choose again.")

if __name__ == '__main__':
    calculator()