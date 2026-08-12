% Guess My Number
% A simple game where the user tries to guess a randomly generated number within a specified range.

% Set the range for the random number
min_value = 1;
max_value = 100;

% Generate a random number within the range
target_number = randi([min_value, max_value]);

% Initialize the number of attempts
attempts = 0;

% Start the game loop
while true
    % Ask the user to guess the number
    guess = input('Guess my number between ' + num2str(min_value) + ' and ' + num2str(max_value) + ': ', 's');
    
    % Convert the input to a numeric value
    guess = str2num(guess);
    
    % Check if the guess is within the range
    if isnan(guess) || (guess < min_value || guess > max_value)
        disp('Invalid input. Please enter a number between ' + num2str(min_value) + ' and ' + num2str(max_value) + '.');
        continue;
    end
    
    % Check if the guess is correct
    if guess == target_number
        disp(['Congratulations! You guessed my number in ' num2str(attempts+1) ' attempts.']);
        break;
    else
        attempts = attempts + 1;
        
        % Give a hint: higher or lower than the guess
        if guess < target_number
            disp('Too low! Try again.');
        elseif guess > target_number
            disp('Too high! Try again.');
        end
    end
end