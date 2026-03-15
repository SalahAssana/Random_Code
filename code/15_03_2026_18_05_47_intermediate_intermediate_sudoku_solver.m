% Sudoku Solver in MATLAB
%
% This program uses logic and algorithms to solve Sudoku puzzles of varying difficulty.

function sudokuSolver()
    % Read the Sudoku puzzle from file (or generate one randomly)
    sudokuPuzzle = readSudokuPuzzle();

    % Initialize the solution array with zeros
    solution = zeros(9, 9);

    % Solve the Sudoku puzzle using backtracking algorithm
    solveSudoku(sudokuPuzzle, solution);

    % Print the solved Sudoku puzzle
    printSudoku(solution);
end

function sudokuArray = readSudokuPuzzle()
    % Read a random Sudoku puzzle from file (replace with your own implementation)
    sudokuFile = 'sudoku_puzzle.txt';
    fileID = fopen(sudokuFile, 'r');
    if fileID == -1
        error('Failed to open the Sudoku puzzle file.');
    end
    sudokuArray = fscanf(fileID, '%d', [9 9]);
    fclose(fileID);
end

function solveSudoku(puzzle, solution)
    % Solve the Sudoku puzzle using backtracking algorithm
    for i = 1:9
        for j = 1:9
            if isBlankCell(puzzle, i, j)
                for num = 1:9
                    if isValidMove(puzzle, i, j, num)
                        puzzle(i, j) = num;
                        solveSudoku(puzzle, solution);
                        if isSolved(puzzle)
                            printSudoku(solution);
                            return;
                        end
                        puzzle(i, j) = 0; % Backtrack: reset the cell to blank
                    end
                end
            end
        end
    end
end

function isValidMove(puzzle, row, col, num)
    % Check if it's a valid move (i.e., the number can be placed in that position without violating Sudoku rules)
    % Check rows and columns for presence of the number
    if any(puzzle(row, :) == num) || any(puzzle(:, col) == num)
        return false;
    end

    % Check the 3x3 sub-grid for presence of the number
    startRow = (row - 1) * 3 + 1;
    startCol = (col - 1) * 3 + 1;
    for i = 1:3
        for j = 1:3
            if puzzle(startRow + i - 1, startCol + j - 1) == num
                return false;
            end
        end
    end

    return true;
end

function isSolved(puzzle)
    % Check if the Sudoku puzzle has been solved (i.e., all cells are filled with valid values)
    for i = 1:9
        for j = 1:9
            if puzzle(i, j) == 0
                return false;
            end
        end
    end

    return true;
end

function printSudoku(sudoku)
    % Print the Sudoku puzzle in a readable format
    fprintf('   ');
    for i = 1:9
        fprintf('%2d ', i);
    end
    fprintf('\n');
    fprintf('   ');
    for i = 1:3
        fprintf('-');
    end
    fprintf('+');
    for i = 1:3
        fprintf('-');
    end
    fprintf('\n');
    for i = 1:9
        fprintf('%2d ', i);
        for j = 1:9
            fprintf('%2d ', sudoku(i, j));
        end
        fprintf('\n');
        if mod(i, 3) == 0
            fprintf('   ');
            for i = 1:3
                fprintf('-');
            end
            fprintf('+');
            for i = 1:3
                fprintf('-');
            end
            fprintf('\n');
        end
    end
end

function isBlankCell(puzzle, row, col)
    % Check if a cell in the Sudoku puzzle is blank (i.e., contains zero)
    return puzzle(row, col) == 0;
end

sudokuSolver();