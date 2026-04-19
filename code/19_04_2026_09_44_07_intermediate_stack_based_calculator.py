def is_operator(token):
    operators = ['+', '-', '*', '/']
    return token in operators

def evaluate_postfix(expression):
    stack = []
    tokens = expression.split()
    
    for token in tokens:
        if is_operator(token):
            b = stack.pop()
            a = stack.pop()
            result = eval(f"{a} {token} {b}")
            stack.append(result)
        else:
            stack.append(float(token))
            
    return stack[0]

def main():
    expressions = ['3 4 +', '10 5 *', '2 3 -', '7 9 /']
    
    for expression in expressions:
        try:
            result = evaluate_postfix(expression)
            print(f"Expression: {expression}, Result: {result}")
        except Exception as e:
            print(f"Error evaluating expression: {e}")

if __name__ == '__main__':
    main()