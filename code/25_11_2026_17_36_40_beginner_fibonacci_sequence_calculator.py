# Fibonacci Sequence Calculator
# Complexity Level: BEGINNER

def fibonacci(n):
    fib_sequence = [0, 1]
    while len(fib_sequence) < n:
        fib_sequence.append(fib_sequence[-1] + fib_sequence[-2])
    return fib_sequence

if __name__ == '__main__':
    n = int(input("Enter the number of Fibonacci numbers to calculate: "))
    fib_numbers = fibonacci(n)
    print("The first {} Fibonacci numbers are:".format(n))
    for i, num in enumerate(fib_numbers):
        print("Fibonacci #{}: {}".format(i+1, num))