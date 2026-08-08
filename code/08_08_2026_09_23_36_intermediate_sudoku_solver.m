% Sudoku Solver
function sudokuSolver(board)
    % Check if board is valid
    if ~isvalidBoard(board)
        error('Invalid Board');
    end
    
    % Initialize empty solution matrix
    sol = zeros(9, 9);
    
    % Call recursive function to solve the puzzle
    solvePuzzle(board, sol);
end

% Helper functions

function result = isvalidBoard(board)
    % Check if board has correct dimensions
    if size(board, 1) ~= 9 || size(board, 2) ~= 9
        result = false;
    else
        result = true;
        for i = 1:9
            for j = 1:9
                if board(i,j) < 0 || board(i,j) > 9
                    result = false;
                    return;
                end
            end
        end
    end
end

function solvePuzzle(board, sol)
    % Find the first empty cell in the board
    [i, j] = find(board == 0);
    
    % If no more cells can be filled, we're done!
    if isempty(i)
        disp('Solved!');
        return;
    end
    
    % Try each possible number for the current cell
    for num = 1:9
        % Check if number is already in the same row or column
        if any(sol(:, j) == num) || any(sol(i, :) == num)
            continue;
        end
        
        % Check if number can be placed in the same 3x3 block
        for k = 1:3
            if any(board((i-1)/3*3+k, (j-1)/3*3+1:j/3*3) == num)
                continue;
                break;
            end
        end
        
        % Place the number in the solution matrix
        sol(i, j) = num;
        
        % Recursively try to fill the rest of the board
        solvePuzzle(board, sol);
        
        % If we return from the recursive call, this means the current cell was not valid
        if any(sol(:, j) ~= 0)
            sol(i, j) = 0;  % Reset the cell to empty
        end
    end
end

% Synthetic data for testing
board = [
    5 3 4 6 7 8 9 1 2;
    6 7 2 1 9 5 3 4 8;
    1 9 8 3 4 2 5 6 7;
    8 5 9 7 6 1 4 2 3;
    4 2 6 8 5 3 7 9 1;
    7 1 3 9 2 4 8 5 6;
    9 6 1 5 3 7 2 8 4;
    2 8 7 4 1 9 6 3 5;
    3 4 5 2 8 6 1 7 9
];

sudokuSolver(board);