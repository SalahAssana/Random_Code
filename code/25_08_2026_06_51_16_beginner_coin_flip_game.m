% Coin Flip Game
% 
% This is a simple game where the user tries to flip a virtual coin to get heads or tails.

% Initialize the number of flips and the wins/losses counts
numFlips = 0;
wins = 0;
losses = 0;

while true
    % Ask the user if they want to play again
    playAgain = input('Do you want to flip a coin? (y/n) ', 's');
    
    if strcmp(playAgain, 'n')
        break
    end
    
    % Generate a random number between 0 and 1
    flipResult = rand;
    
    % Determine the result of the flip
    if flipResult < 0.5
        result = 'Heads';
    else
        result = 'Tails';
    end
    
    % Ask the user to guess the result
    guess = input('What is your guess? (h/t) ', 's');
    
    if strcmp(guess, 'h') && strcmp(result, 'Heads')
        wins = wins + 1;
    elseif strcmp(guess, 't') && strcmp(result, 'Tails')
        wins = wins + 1;
    else
        losses = losses + 1;
    end
    
    % Display the result and update the counts
    disp([num2str(numFlips+1), '. The coin landed on ', result]);
    disp(['You got it right ', num2str(wins), ' times, wrong ', num2str(losses), ' times.']);
    
    numFlips = numFlips + 1;
end

% Display the final counts
disp(['Final results: You got it right ', num2str(wins), ' times, wrong ', num2str(losses), ' times.']);