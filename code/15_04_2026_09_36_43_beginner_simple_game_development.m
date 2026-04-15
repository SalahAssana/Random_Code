% Simple Tic-Tac-Toe Game in MATLAB

% Define the game board as an array of zeros
board = zeros(3, 3);

% Function to print the game board
function printBoard()
    for i = 1:3
        for j = 1:3
            if board(i, j) == 0
                fprintf(' ');
            elseif board(i, j) == 1
                fprintf('X');
            else
                fprintf('O');
            end
            fprintf('\t');
        end
        fprintf('\n');
    end
end

% Function to check for a winner
function isWinner = checkForWinner()
    % Check rows
    for i = 1:3
        if board(i, 1) == board(i, 2) && board(i, 2) == board(i, 3)
            isWinner = true;
            return
        end
    end
    
    % Check columns
    for i = 1:3
        if board(1, i) == board(2, i) && board(2, i) == board(3, i)
            isWinner = true;
            return
        end
    end
    
    % Check diagonals
    if board(1, 1) == board(2, 2) && board(2, 2) == board(3, 3)
        isWinner = true;
        return
    end
    if board(1, 3) == board(2, 2) && board(2, 2) == board(3, 1)
        isWinner = true;
        return
    end
    
    % If no winner, set to false
    isWinner = false;
end

% Main game loop
while true
    % Print the current state of the board
    printBoard();
    
    % Ask the user for their move (X or O)
    playerMove = input('Enter your move (1-9), or Q to quit: ', 's');
    
    % Convert the input to a numeric value
    if strcmp(playerMove, 'Q')
        break;
    end
    moveNum = str2double(playerMove);
    
    % Validate the input
    if isnan(moveNum) || moveNum < 1 || moveNum > 9
        fprintf('Invalid input. Please try again.\n');
        continue
    end
    
    % Convert the move number to board coordinates
    row = ceil(mod(moveNum, 3));
    col = floor((moveNum - 1) / 3);
    
    % Check if the move is valid (i.e., the space is empty)
    if board(row, col) ~= 0
        fprintf('Invalid move. That space is already occupied.\n');
        continue
    end
    
    % Update the game board with the user's move
    board(row, col) = mod(moveNum - 1, 2) + 1;
    
    % Check if there is a winner after the current move
    isWinner = checkForWinner();
    
    % If there is a winner, print the final state of the board and exit
    if isWinner
        printBoard();
        fprintf('Congratulations! You won.\n');
        break
    end
end

% Print the final state of the board (or "Game Over" if the game ended)
printBoard();

% Print a message indicating the outcome of the game
if isWinner
    fprintf('Congratulations! You won.\n');
else
    fprintf('Game Over. Better luck next time!\n');