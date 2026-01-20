% Prime Number Checker
% Description: Checks if a given number is prime and displays a message accordingly.

function check_prime()
    % Read input from user
    num = input('Enter a number: ');

    % Check if the number is less than 2 (not prime)
    if num < 2
        disp('The number is not prime.');
    else
        % Check if the number is divisible by any number up to its square root
        for i = 2:sqrt(num)
            if mod(num, i) == 0
                disp(['The number ' num ' is not prime.']);
                return
            end
        end

        % If no divisors found, the number is prime
        disp(['The number ' num ' is prime.']);
    end
end

% Call the function
check_prime();