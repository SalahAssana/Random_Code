% Rock, Paper, Scissors Game
% BEGINNER Complexity Project

% Initialize scores
userScore = 0;
computerScore = 0;

while true
    % Ask user for input
    choice = input('Enter your move (rock/paper/scissors): ', 's');
    
    % Convert to lowercase
    choice = lower(choice);
    
    % Generate computer's random move
    moves = {'rock', 'paper', 'scissors'};
    computerChoice = moves{randi([1 3], 1)};
    
    % Determine winner
    if strcmp(choice, computerChoice)
        fprintf('It''s a tie!\n');
    elseif (strcmp(choice, 'rock') && strcmp(computerChoice, 'scissors')) || ...
           (strcmp(choice, 'paper') && strcmp(computerChoice, 'rock')) || ...
           (strcmp(choice, 'scissors') && strcmp(computerChoice, 'paper'))
        fprintf('You win!\n');
        userScore = userScore + 1;
    else
        fprintf('Computer wins!\n');
        computerScore = computerScore + 1;
    end
    
    % Display scores
    fprintf('User: %d - Computer: %d\n', userScore, computerScore);
    
    % Ask if user wants to play again
    playAgain = input('Do you want to play again? (y/n): ', 's');
    
    % Convert to lowercase
    playAgain = lower(playAgain);
    
    % Exit the game if user chooses not to play again
    while strcmp(playAgain, 'n')
        fprintf('Thanks for playing!\n');
        break;
    end