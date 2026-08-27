% Guessing Game with Random Numbers
% Author: [Your Name]

% Initialize game variables
attempts = 0;
num_to_guess = randi([1 100], 1); % Generate random number between 1 and 100
is_winner = false;

while ~is_winner
    % Ask player for guess
    disp('Guess a number between 1 and 100:');
    guess = input('');
    
    % Check if guess is correct
    if guess == num_to_guess
        disp(['Congratulations! You guessed the number in ' num2str(attempts + 1) ' attempts.']);
        is_winner = true;
    else
        % Increment attempt count
        attempts = attempts + 1;
        
        % Display hint: higher or lower than previous guess
        if guess < num_to_guess
            disp('The number is higher than your guess.');
        elseif guess > num_to_guess
            disp('The number is lower than your guess.');
        end
    end
end

% End of game message