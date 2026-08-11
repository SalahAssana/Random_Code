# Simple Calculator Program

def calculate(expression):
    # Evaluate the given mathematical expression
    result = eval(expression)
    return result

def main():
    if __name__ == '__main__':
        print("Simple Calculator")
        while True:
            user_input = input("Enter a math expression (or 'q' to quit): ")
            if user_input.lower() == 'q':
                break
            try:
                print("Result:", calculate(user_input))
            except Exception as e:
                print("Error: ", str(e))

if __name__ == '__main__':
    main()