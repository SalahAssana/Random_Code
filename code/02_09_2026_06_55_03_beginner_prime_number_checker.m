% Prime Number Checker in MATLAB
% This program takes an integer as input and checks if it's prime or not

% Input: An integer number
num = input('Enter a positive integer: ');

% Function to check if a number is prime
function isPrime = checkPrime(n)
    % Initialize a flag variable to assume the number is prime
    isPrime = true;
    
    % Check for numbers less than 2 (not prime)
    if n < 2
        isPrime = false;
    % Check for numbers divisible by 2 (not prime)
    elseif mod(n,2) == 0
        isPrime = false;
    % Check divisibility from 3 to sqrt(n)
    else
        for i = 3:sqrt(n)
            if mod(n,i) == 0
                isPrime = false;
                break;
            end
        end
    end
end

% Call the function and display the result
isPrime = checkPrime(num);
if isPrime
    disp(['The number ' num ' is a prime number.']);
else
    disp(['The number ' num ' is not a prime number.']);
end