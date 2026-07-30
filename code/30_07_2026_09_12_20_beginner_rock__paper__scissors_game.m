% Rock, Paper, Scissors Game
% Beginner level implementation in MATLAB

% Initialize score counters
userScore = 0;
computerScore = 0;

while true
    % Get user input (1-3)
    choice = input('Enter your move (1-Rock, 2-Paper, 3-Scissors): ', 's');
    
    % Validate user input
    if strcmp(choice, '1') || strcmp(choice, '2') || strcmp(choice, '3')
        break;
    else
        disp('Invalid input. Please try again.');
    end
end

% Generate computer's random move (1-3)
computerChoice = randi([1 3], 1);

% Determine the winner based on game rules
if choice == 1 && computerChoice == 2 || ...
   choice == 2 && computerChoice == 3 || ...
   choice == 3 && computerChoice == 1
    userScore = userScore + 1;
else
    computerScore = computerScore + 1;
end

% Display the result
disp(['User score: ', num2str(userScore)]);
disp(['Computer score: ', num2str(computerScore)]);

if userScore > computerScore
    disp('You win!');
elseif userScore < computerScore
    disp('Computer wins.');
else
    disp('It''s a tie!');