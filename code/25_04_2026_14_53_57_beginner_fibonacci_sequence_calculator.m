% Fibonacci Sequence Calculator
% BEGINNER complexity project

% Define function for recursive approach
function fib_recursive(n)
    if n <= 1
        fib_recursive_result = n;
    else
        fib_recursive_result = fib_recursive(n-1) + fib_recursive(n-2);
    end
end

% Define function for iterative approach
function fib_iterative(n)
    a = 0;
    b = 1;
    if n <= 1
        fib_iterative_result = a;
    elseif n == 2
        fib_iterative_result = b;
    else
        for i = 3:n
            c = a + b;
            a = b;
            b = c;
        end
        fib_iterative_result = b;
    end
end

% Main script
n = input('Enter the number of terms: ');
disp('Fibonacci sequence using recursive approach:');
for i = 1:n
    disp(fib_recursive(i));
end

disp(' ');
disp('Fibonacci sequence using iterative approach:');
for i = 1:n
    disp(fib_iterative(i));
end