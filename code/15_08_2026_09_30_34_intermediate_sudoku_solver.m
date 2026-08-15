% Sudoku Solver Script

% Import necessary libraries
import java.lang.System;

% Define the Sudoku struct to hold puzzle data
struct Sudoku
    grid;
    rowConstraints;
    colConstraints;
    boxConstraints;
end

% Define the solve function
function solvedGrid = solve(sudoku)
    % Initialize an empty grid for the solution
    solvedGrid = zeros(9, 9);

    % Function to check if a number can be placed in a given cell
    function isValid(num, sudoku, row, col)
        % Check row constraint
        for i = 1:9
            if sudoku.rowConstraints(row, i) == num
                return false;
            end
        end

        % Check column constraint
        for i = 1:9
            if sudoku.colConstraints(col, i) == num
                return false;
            end
        end

        % Check box constraint
        startRow = mod(row - 1, 3) + 1;
        startCol = floor((col - 1) / 3) + 1;

        for i = 1:3
            for j = 1:3
                if sudoku.grid(startRow * 3 + i, startCol * 3 + j) == num
                    return false;
                end
            end
        end

        % If the number is not in any of the constraints, it's valid
        return true;
    end

    % Recursive function to solve the Sudoku puzzle
    function solveRecursively(sudoku, row, col)
        if row > 9 || col > 9
            % We've filled the entire grid, so we're done!
            solvedGrid = sudoku.grid;
            return;
        end

        for num = 1:9
            if isValid(num, sudoku, row, col)
                % Place the number in the cell and recursively solve the rest of the puzzle
                sudoku.grid(row, col) = num;
                solveRecursively(sudoku, row + (col >= 3), mod(col, 3) + 1);

                % If we've filled the entire grid, return
                if all(all(solvedGrid == sudoku.grid))
                    solvedGrid = sudoku.grid;
                    return;
                end

                % Backtrack by resetting the cell to 0 and backtracking up the recursion stack
                sudoku.grid(row, col) = 0;
            end
        end
    end

    % Start solving from the top-left corner of the grid
    solveRecursively(sudoku, 1, 1);
end

% Example usage:
sudokuGrid = [
    5 3 4 6 7 8 9 1 2;
    6 7 2 1 9 5 3 4 8;
    1 9 8 3 4 2 5 6 7;
    8 5 9 7 6 1 4 2 3;
    4 2 6 8 5 3 7 9 1;
    7 1 3 9 2 4 8 5 6;
    9 6 1 5 3 7 2 8 4;
    2 8 4 4 1 9 6 3 7;
    3 4 7 2 8 6 1 5 9
];

sudoku = Sudoku(sudokuGrid, zeros(9, 9), zeros(9, 9), zeros(9, 9));
solvedGrid = solve(sudoku);