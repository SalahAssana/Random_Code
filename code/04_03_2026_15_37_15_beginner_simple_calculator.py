# Simple Calculator
import re

def calculator():
    while True:
        expression = input("Enter mathematical expression (or 'quit' to exit): ")
        if expression.lower() == 'quit':
            break
        
        # Remove whitespace and comments from the expression
        expression = re.sub(r'#.*$', '', expression).strip()
        
        try:
            result = eval(expression)
            print(f"Result: {result}")
        except Exception as e:
            print(f"Error: {str(e)}")

if __name__ == '__main__':