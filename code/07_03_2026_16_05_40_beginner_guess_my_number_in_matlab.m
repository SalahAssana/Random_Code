% Guess My Number in MATLAB
% A simple game where the user tries to guess a randomly generated number within a certain range

% Set the range for the random number generation (1-100)
minValue = 1;
maxValue = 100;

% Generate a random number within the set range
myNumber = randi([minValue maxValue]);

% Initialize the number of attempts
attempts = 0;

% Start the game loop
while true
    % Ask the user to guess a number
    guess = input('Guess a number between 1 and 100: ', 'f');
    
    % Check if the guess is within the valid range
    if guess < minValue || guess > maxValue
        fprintf('Invalid guess! Try again.\n');
        continue;
    end
    
    % Increment the attempt counter
    attempts = attempts + 1;
    
    % Check if the user's guess matches the randomly generated number
    if guess == myNumber
        fprintf(['Congratulations! You guessed it in ' num2str(attempts) ' attempts.\n']);
        break;
    else
        % Provide a hint if the guess is not correct
        if guess > myNumber
            fprintf('Too high! Try again.\n');
        else
            fprintf('Too low! Try again.\n');
        end
    end
end