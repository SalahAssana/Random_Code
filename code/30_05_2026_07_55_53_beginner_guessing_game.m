% Guessing Game - A Simple MATLAB Program for Beginners
% 
% This program generates a random number between 1 and 100, then asks the user to guess it.
% The user is given hints about their guesses (too high or too low) until they correctly guess the number.

% Initialize the random number generator with a seed value
rng(0);

% Generate a random number between 1 and 100
numToGuess = randi([1, 100]);

% Initialize the number of attempts to 0
attempts = 0;

% Loop until the user correctly guesses the number
while true
    % Ask the user for their guess
    guess = input('Guess a number between 1 and 100: ', 'f');

    % Check if the guess is within the valid range
    if guess < 1 || guess > 100
        fprintf('Invalid guess. Please enter a number between 1 and 100.\n');
        continue;
    end

    % Increment the number of attempts
    attempts = attempts + 1;

    % Check if the guess is correct
    if guess == numToGuess
        fprintf(['You guessed it in ', num2str(attempts), ' attempts!\n']);
        break;
    elseif guess > numToGuess
        fprintf('Too high! Try again.\n');
    else
        fprintf('Too low! Try again.\n');
    end