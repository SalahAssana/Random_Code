# Calculator Program
# A simple program that takes in mathematical expressions and evaluates them.

def calculate(expression):
    # Try to evaluate the expression using eval()
    try:
        result = eval(expression)
        return str(result)
    except Exception as e:
        return "Error: " + str(e)

if __name__ == '__main__':
    while True:
        user_input = input("Enter a mathematical expression (or 'quit' to exit): ")
        
        if user_input.lower() == 'quit':
            break
        
        result = calculate(user_input)
        print("Result:", result)