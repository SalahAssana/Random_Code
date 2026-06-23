# Simple Calculator in Python
def add(x, y):
    """Add two numbers"""
    return x + y

def subtract(x, y):
    """Subtract one number from another"""
    return x - y

def multiply(x, y):
    """Multiply two numbers"""
    return x * y

def divide(x, y):
    """Divide one number by another"""
    if y == 0:
        return "Error: Division by zero"
    else:
        return x / y

def calculator():
    """Main function for calculator"""
    print("Simple Calculator")
    while True:
        user_input = input("Enter a mathematical expression (or 'q' to quit): ")
        
        if user_input.lower() == 'q':
            break
            
        try:
            result = eval(user_input)
            print(f"Result: {result}")
        except Exception as e:
            print(f"Error: {str(e)}")

if __name__ == '__main__':
    calculator()