def fibonacci(n):
    a, b = 0, 1
    result = []
    for i in range(n):
        result.append(a)
        a, b = b, a + b
    return result

def main():
    n = int(input("Enter the number of Fibonacci numbers to generate: "))
    fib_series = fibonacci(n)
    print(fib_series)

if __name__ == '__main__':
    main()