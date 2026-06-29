% Guess My Number
% A simple program that generates and guesses a random number within a specified range

% Initialize the lower and upper bounds of the number range
lower_bound = 1;
upper_bound = 100;

% Generate a random number within the range
number_to_guess = randi([lower_bound, upper_bound]);

% Initialize the number of attempts to guess the number
attempts = 0;

while true
    % Ask the user for their guess
    user_guess = input('Guess my number (1-' + num2str(upper_bound) + '): ', 'f');

    % Check if the user's guess is within the range
    if user_guess < lower_bound || user_guess > upper_bound
        disp('Invalid guess! Try again.')
        continue
    end

    % Increment the number of attempts
    attempts = attempts + 1;

    % Check if the user's guess matches the generated number
    if user_guess == number_to_guess
        disp([' Congratulations! You guessed my number in ' num2str(attempts) ' attempts.'])
        break
    elseif user_guess < number_to_guess
        disp('Too low! Try again.')
    else
        disp('Too high! Try again.')
    end