# Hello World Calculator
# A simple program that calculates and prints mathematical expressions.

def calculate_expression(expression):
    # Evaluate the expression using eval() function
    result = eval(expression)
    
    return str(result)

def main():
    if __name__ == '__main__':
        print("Hello, World! Let's do some math.")
        
        while True:
            user_input = input("Enter a mathematical expression (or 'q' to quit): ")
            
            if user_input.lower() == 'q':
                break
                
            try:
                result = calculate_expression(user_input)
                print(f"Result: {result}")
            except Exception as e:
                print(f"Error: {str(e)}")

if __name__ == '__main__':
    main()