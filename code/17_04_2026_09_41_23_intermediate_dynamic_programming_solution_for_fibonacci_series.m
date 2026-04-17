% Fibonacci Series using Dynamic Programming

function fib = fibonacci(n)
    % Initialize array to store Fibonacci numbers
    fib = zeros(1, n + 1);

    % Base cases: F(0) = 0 and F(1) = 1
    fib(1) = 0;
    fib(2) = 1;

    for i = 3:n
        % Calculate Fibonacci number using previously computed values
        fib(i) = fib(i - 1) + fib(i - 2);
    end
end

% Test the function with n = 10
n = 10;
result = fibonacci(n);

% Display the result
fprintf('Fibonacci series for %d: [%s]\n', n, strjoin(num2str(result), ', '));