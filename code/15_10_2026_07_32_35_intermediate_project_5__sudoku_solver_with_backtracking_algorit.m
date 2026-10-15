% Project 5: Sudoku Solver with Backtracking Algorithm
% https://www.mathworks.com/help/matlab/numeric-computations.html

function sudokuSolver
    % Define constants for Sudoku grid dimensions
    GRID_SIZE = 9;
    
    % Initialize an empty Sudoku grid as a 2D array (matrix)
    sudokuGrid = zeros(GRID_SIZE, GRID_SIZE);
    
    % Set the initial values for the Sudoku puzzle
    sudokuGrid(1, 1) = 5; 
    sudokuGrid(1, 2) = 3; 
    sudokuGrid(1, 4) = 6; 
    sudokuGrid(2, 2) = 9; 
    sudokuGrid(2, 5) = 7; 
    sudokuGrid(3, 8) = 1; 
    sudokuGrid(3, 6) = 8; 
    sudokuGrid(4, 4) = 3; 
    sudokuGrid(5, 2) = 5; 
    sudokuGrid(5, 7) = 9; 
    sudokuGrid(6, 1) = 7; 
    sudokuGrid(6, 8) = 3; 
    sudokuGrid(7, 4) = 8; 
    sudokuGrid(8, 7) = 2; 
    sudokuGrid(8, 3) = 9; 
    sudokuGrid(9, 5) = 1;
    
    % Define the function to check if a number can be placed in a given cell
    function isValidMove(grid, row, col, num)
        % Check if the given number is already present in the same row
        for i = 1:GRID_SIZE
            if grid(row, i) == num
                return false;
            end
        end
        
        % Check if the given number is already present in the same column
        for i = 1:GRID_SIZE
            if grid(i, col) == num
                return false;
            end
        end
        
        % Check if the given number is already present in the same 3x3 sub-grid
        startRow = floor((row - 1) / 3) * 3 + 1;
        startCol = floor((col - 1) / 3) * 3 + 1;
        
        for i = 1:3
            for j = 1:3
                if grid(startRow+i-1, startCol+j-1) == num
                    return false;
                end
            end
        end
        
        % If the number is not present in any of the above checks, it's a valid move
        return true;
    end
    
    % Define the function to solve the Sudoku puzzle using backtracking
    function sudokuGrid = solveSudoku(grid)
        for row = 1:GRID_SIZE
            for col = 1:GRID_SIZE
                if grid(row, col) == 0
                    for num = 1:GRID_SIZE
                        if isValidMove(grid, row, col, num)
                            % Place the number in the cell and recursively try to solve the puzzle
                            grid(row, col) = num;
                            sudokuGrid = solveSudoku(grid);
                            
                            % If a solution is found, return the solved grid
                            if all(all(sudokuGrid ~= 0))
                                return;
                            end
                            
                            % If no solution is found, backtrack and reset the cell to 0
                            grid(row, col) = 0;
                        end
                    end
                    
                    % If no valid number can be placed in the cell, backtrack and reset the cell to 0
                    if all(grid(row, :) == 0)
                        return;
                    end
                end
            end
        end
        
        % If a solution is found, return the solved grid
        if all(all(sudokuGrid ~= 0))
            return sudokuGrid;
        else
            % If no solution is found, display an error message and exit
            disp('No solution exists for this Sudoku puzzle.');
            return;
        end
    end
    
    % Call the solveSudoku function to solve the Sudoku puzzle
    sudokuGrid = solveSudoku(sudokuGrid);
    
    % Display the solved Sudoku grid
    disp(sudokuGrid);
end
