def fibonacci(n):
    a, b = 0, 1
    result = []
    for i in range(n):
        result.append(a)
        a, b = b, a + b
    return result

if __name__ == '__main__':
    num_terms = int(input("Enter the number of terms: "))
    fib_series = fibonacci(num_terms)
    print(fib_series)