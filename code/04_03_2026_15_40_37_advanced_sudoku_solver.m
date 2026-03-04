% Sudoku Solver
classdef SudokuSolver
    methods(Static)
        function solve(board)
            % Initialize variables
            emptyCells = findEmptyCell(board);
            if isempty(emptyCells)
                % If all cells are filled, return the board
                displayBoard(board);
                return;
            end
            
            for i = 1:size(emptyCells, 1)
                cell = emptyCells(i, :);
                for num = 1:9
                    if isValidMove(cell, num, board)
                        board(cell(1), cell(2)) = num;
                        solve(board);
                        % If the recursive call returns without filling the current cell,
                        % then the move was not valid and we should backtrack
                        if board(cell(1), cell(2)) ~= num
                            board(cell(1), cell(2)) = 0;
                            return;
                        end
                    end
                end
            end
        end
        
        function emptyCells = findEmptyCell(board)
            % Find all empty cells in the board
            emptyCells = [];
            for i = 1:9
                for j = 1:9
                    if board(i, j) == 0
                        emptyCells = [emptyCells; [i j]];
                    end
                end
            end
        end
        
        function isValidMove(cell, num, board)
            % Check if the given number can be placed in the given cell
            row = cell(1);
            col = cell(2);
            
            % Check the row for repeated numbers
            if any(board(row, :) == num)
                return false;
            end
            
            % Check the column for repeated numbers
            if any(board(:, col) == num)
                return false;
            end
            
            % Check the box for repeated numbers
            startRow = floor((row - 1) / 3) * 3 + 1;
            startCol = floor((col - 1) / 3) * 3 + 1;
            for i = startRow:startRow+2
                for j = startCol:startCol+2
                    if board(i, j) == num
                        return false;
                    end
                end
            end
            
            % If we have not returned by now, the move is valid
            return true;
        end
        
        function displayBoard(board)
            % Display the Sudoku board
            for i = 1:9
                for j = 1:9
                    if board(i, j) < 10
                        fprintf('%d ', board(i, j));
                    else
                        fprintf('0 ');
                    end
                end
                fprintf('\n');
            end
        end
    end
end

% Test the Sudoku Solver
board = [0 0 0 0 0 0 0 0 0;
         0 8 0 0 3 0 0 9 0;
         0 0 0 9 0 7 0 0 0;
         0 0 0 0 1 2 0 0 6;
         0 5 0 0 8 4 0 3 0;
         0 0 0 4 0 5 0 0 9;
         0 7 0 0 0 0 8 1 0;
         0 0 9 6 0 0 0 2 0;
         0 3 0 0 0 0 4 8 0];
        
SudokuSolver.solve(board);