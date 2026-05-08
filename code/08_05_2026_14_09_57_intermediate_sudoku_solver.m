% Sudoku Solver
% Author: [Your Name]

function solvedBoard = sudokuSolver(board)
    % Check if the board is valid
    if ~isValidBoard(board)
        error('Invalid board');
    end
    
    % Find empty cells
    emptyCells = findEmptyCells(board);
    
    % Solve using backtracking
    solvedBoard = solveUsingBacktracking(board, emptyCells);
end

function isValidBoard = isValidBoard(board)
    % Check rows
    for i = 1:size(board, 1)
        row = board(i, :);
        if ~isValidRow(row)
            return;
        end
    end
    
    % Check columns
    for j = 1:size(board, 2)
        col = board(:, j);
        if ~isValidColumn(col)
            return;
        end
    end
    
    % Check blocks
    for i = 1:3
        for j = 1:3
            block = board((i-1)*3+1:(i*3), (j-1)*3+1:j*3);
            if ~isValidBlock(block)
                return;
            end
        end
    end
    
    isValidBoard = true;
end

function rowIsValid = isValidRow(row)
    % Check for duplicate values in the row
    uniqueValues = unique(row);
    if size(uniqueValues, 2) ~= size(row, 2)
        rowIsValid = false;
    else
        rowIsValid = true;
    end
end

function colIsValid = isValidColumn(col)
    % Check for duplicate values in the column
    uniqueValues = unique(col);
    if size(uniqueValues, 2) ~= size(col, 2)
        colIsValid = false;
    else
        colIsValid = true;
    end
end

function blockIsValid = isValidBlock(block)
    % Check for duplicate values in the block
    uniqueValues = unique(block(:));
    if size(uniqueValues, 2) ~= size(block, 1)*size(block, 2)
        blockIsValid = false;
    else
        blockIsValid = true;
    end
end

function emptyCells = findEmptyCells(board)
    % Find all empty cells (represented by 0)
    emptyCells = find(board == 0);
end

function solvedBoard = solveUsingBacktracking(board, emptyCells)
    % Try numbers from 1 to 9 in the first empty cell
    for i = 1:9
        board(emptyCells(1), emptyCells(2)) = i;
        
        % Check if the board is valid after placing the number
        if isValidBoard(board)
            if length(emptyCells) == 1
                solvedBoard = board;
                return;
            else
                solvedBoard = solveUsingBacktracking(board, findEmptyCells(board));
                if ~isempty(solvedBoard)
                    return;
                end
            end
        end
        
        % If the number doesn't work, backtrack by resetting the cell to 0
        board(emptyCells(1), emptyCells(2)) = 0;
    end
    
    solvedBoard = [];
end

% Synthetic data for testing
board = [
    5, 3, 0, 0, 7, 0, 0, 0, 0,
    6, 0, 0, 1, 9, 5, 0, 0, 0,
    0, 9, 8, 0, 0, 0, 0, 6, 0,
    8, 0, 0, 0, 6, 0, 0, 0, 3,
    4, 0, 0, 8, 0, 3, 0, 0, 1,
    7, 0, 0, 0, 2, 0, 0, 0, 6,
    0, 6, 0, 0, 0, 0, 2, 8, 0,
    0, 0, 0, 4, 1, 9, 0, 0, 5,
    0, 0, 0, 0, 8, 0, 0, 7, 9
];

% Solve the Sudoku puzzle
solvedBoard = sudokuSolver(board);

% Display the solved board
disp(solvedBoard);