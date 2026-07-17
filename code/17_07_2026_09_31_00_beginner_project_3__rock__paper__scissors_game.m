% Project 3: Rock, Paper, Scissors Game
% Author: [Your Name]
% Date: [Date]

% Define possible choices for user and computer
choices = {'rock', 'paper', 'scissors'};

% Initialize score for user and computer
user_score = 0;
computer_score = 0;

% Main game loop
while true
    % Get user choice
    choice = input('Enter your choice (rock, paper, scissors), or "q" to quit: ', 's');
    
    % Check if user wants to quit
    if strcmp(choice, 'q')
        break;
    end
    
    % Validate user choice
    if ~any(strcmp(choice, choices))
        disp('Invalid choice. Please try again.');
        continue;
    end
    
    % Generate random computer choice
    computer_choice = choices{randi([1 3], 1)};
    
    % Determine winner
    if strcmp(choice, computer_choice)
        disp(['It''s a tie! Both players chose ' choice '.']);
    elseif (strcmp(choice, 'rock') && strcmp(computer_choice, 'scissors')) || ...
           (strcmp(choice, 'paper') && strcmp(computer_choice, 'rock')) || ...
           (strcmp(choice, 'scissors') && strcmp(computer_choice, 'paper'))
        user_score = user_score + 1;
        disp(['User wins! User chose ' choice ', and computer chose ' computer_choice '.']);
    else
        computer_score = computer_score + 1;
        disp(['Computer wins! User chose ' choice ', and computer chose ' computer_choice '.']);
    end
    
    % Display current score
    disp(['Score - User: ' num2str(user_score) ', Computer: ' num2str(computer_score)]);
end

% Display final score
disp(['Final Score - User: ' num2str(user_score) ', Computer: ' num2str(computer_score)]);

% If user won, congratulate them. Otherwise, encourage them to play again.
if user_score > computer_score
    disp('Congratulations! You won the game!');
else
    disp('Better luck next time! Do you want to play again?');
end