def fibonacci(n):
    sequence = [0, 1]
    while sequence[-1] + sequence[-2] <= n:
        sequence.append(sequence[-1] + sequence[-2])
    return sequence

if __name__ == '__main__':
    num_terms = int(input("Enter the number of terms in the Fibonacci sequence: "))
    print(f"Fibonacci sequence up to {num_terms}: {fibonacci(num_terms)}")