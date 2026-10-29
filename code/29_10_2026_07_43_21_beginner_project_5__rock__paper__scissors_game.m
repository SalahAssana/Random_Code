% Project 5: Rock, Paper, Scissors Game
% Complexity Level: BEGINNER

% Initialize score
score = [0 0]; % [wins losses]

while true
    % Ask user for their choice (1-3)
    user_choice = input('Enter your choice (1-rock, 2-paper, 3-scissors): ', 's');
    
    % Validate user input
    if ~strcmp(user_choice, '1') && ~strcmp(user_choice, '2') && ~strcmp(user_choice, '3')
        error('Invalid input. Please enter 1, 2 or 3.')
    end
    
    % Generate computer choice (randomly)
    choices = {'rock', 'paper', 'scissors'};
    computer_choice = choices{randi([1 3], 1)};
    
    % Determine the winner
    if strcmp(computer_choice, 'rock') && strcmp(user_choice, '2')
        score(1) = score(1) + 1;
    elseif strcmp(computer_choice, 'paper') && (strcmp(user_choice, '1') || strcmp(user_choice, '3'))
        score(1) = score(1) + 1;
    elseif strcmp(computer_choice, 'scissors') && (strcmp(user_choice, '2') || strcmp(user_choice, '1'))
        score(1) = score(1) + 1;
    else
        score(2) = score(2) + 1;
    end
    
    % Display the result
    if score(1) > score(2)
        fprintf('You win! Your score is %d-%d.\n', score(1), score(2));
    elseif score(2) > score(1)
        fprintf('Computer wins! The score is %d-%d.\n', score(1), score(2));
    else
        fprintf('It''s a tie! The score is %d-%d.\n', score(1), score(2));
    end
    
    % Ask if the user wants to play again
    response = input('Do you want to play again? (y/n): ', 's');
    
    % Exit the game if the user chooses not to play again
    if ~strcmp(response, 'y')
        break;
    end
end

% Display final score
fprintf('Final score: You - %d, Computer - %d.\n', score(1), score(2));