% Simple Rock, Paper, Scissors Game

% Define possible choices for players
choices = {'rock', 'paper', 'scissors'};

% Get user input
player1Choice = input('Player 1, enter your choice (rock, paper, scissors): ', 's');
player2Choice = input('Player 2, enter your choice (rock, paper, scissors): ', 's');

% Check if player inputs are valid choices
if ~any(strcmpi(choices, player1Choice) | strcmpi(choices, player2Choice))
    error('Invalid choice. Please choose from rock, paper, or scissors.')
end

% Determine the winner based on game rules
if strcmpi(player1Choice, player2Choice)
    winner = 'It''s a tie!';
elseif (strcmpi(player1Choice, 'rock') && strcmpi(player2Choice, 'scissors')) || ...
       (strcmpi(player1Choice, 'paper') && strcmpi(player2Choice, 'rock')) || ...
       (strcmpi(player1Choice, 'scissors') && strcmpi(player2Choice, 'paper'))
    winner = 'Player 1 wins!';
else
    winner = 'Player 2 wins!';
end

% Display the result
fprintf('The winner is: %s\n', winner);