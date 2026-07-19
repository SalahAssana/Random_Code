% Guessing Game
% A simple game where the user tries to guess a random number between 1 and 100.

% Initialize the random number to be guessed
secretNumber = randi([1, 100]);

% Initialize the number of attempts made by the user
attempts = 0;

% Start the game loop
while true
    % Ask the user for their guess
    prompt = 'Guess a number between 1 and 100: ';
    guess = input(prompt);

    % Check if the guess is valid (within range)
    if guess < 1 || guess > 100
        fprintf('Invalid guess. Please try again.\n');
        continue;
    end

    % Increment the number of attempts made by the user
    attempts = attempts + 1;

    % Check if the guess is correct
    if guess == secretNumber
        fprintf(' Congratulations! You guessed the number in %d attempts.\n', attempts);
        break;
    elseif guess < secretNumber
        fprintf('Too low. Try again.\n');
    else
        fprintf('Too high. Try again.\n');
    end
end