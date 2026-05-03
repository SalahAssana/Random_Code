% Optimized Sudoku Solver
classdef SudokuSolver < handle
    properties
        puzzle
        solution
    end
    
    methods
        function obj = SudokuSolver(puzzle)
            obj.puzzle = puzzle;
            obj.solution = zeros(size(puzzle));
        end
        
        function solve(obj, maxAttempts)
            attempts = 0;
            while ~isSolved(obj) && attempts < maxAttempts
                [row, col] = findUnsolved(obj);
                if isempty(row)
                    % No more unsolved cells, puzzle is solved or has no solution
                    return
                end
                numbers = getAvailableNumbers(obj, row, col);
                for num = 1:length(numbers)
                    obj.solution(row, col) = numbers(num);
                    if ~isSolved(obj)
                        attempts = attempts + 1;
                        obj = solve(obj, maxAttempts - attempts);
                        if ~isempty(obj.solution)
                            return
                        end
                    else
                        obj.solution(row, col) = 0; % Backtrack
                    end
                end
            end
        end
        
        function [row, col] = findUnsolved(obj)
            for row = 1:size(obj.puzzle, 1)
                for col = 1:size(obj.puzzle, 2)
                    if obj.puzzle(row, col) == 0
                        [row, col]
                        return
                    end
                end
            end
        end
        
        function numbers = getAvailableNumbers(obj, row, col)
            numbers = 1:9;
            for i = 1:3
                numRow = (row - 1) * 3 + i;
                if ~isempty(find(obj.puzzle(numRow, :) == obj.puzzle(row, col)))
                    numbers(numRow, :) = [];
                end
            end
            for j = 1:3
                numCol = (col - 1) * 3 + j;
                if ~isempty(find(obj.puzzle(:, numCol) == obj.puzzle(row, col)))
                    numbers(numCol, :) = [];
                end
            end
            rowStart = (row - 1) / 3 * 3;
            colStart = (col - 1) / 3 * 3;
            for i = 1:3
                for j = 1:3
                    if obj.puzzle(rowStart + i, colStart + j) == obj.puzzle(row, col)
                        numbers((rowStart + i) * 9 + (colStart + j), :) = [];
                    end
                end
            end
        end
        
        function b = isSolved(obj)
            for row = 1:size(obj.puzzle, 1)
                for col = 1:size(obj.puzzle, 2)
                    if obj.puzzle(row, col) == 0
                        b = false;
                        return
                    end
                end
            end
            b = true;
        end
    end
    
end

% Test the Sudoku Solver
puzzle = [
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

solver = SudokuSolver(puzzle);
solver.solve(10000);