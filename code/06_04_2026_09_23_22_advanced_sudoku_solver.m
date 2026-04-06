% Sudoku Solver
classdef SudokuSolver < handle
    methods
        function obj = SudokuSolver(boardSize)
            % Constructor
            obj.boardSize = boardSize;
            obj.board = zeros(1,obj.boardSize^2);
            obj.solvedBoard = zeros(obj.boardSize,obj.boardSize);
        end
        
        function solveSudoku(obj,board)
            % Solve Sudoku using backtracking and recursive algorithms
            obj.board = board;
            obj.solveBoard();
        end
        
        function solveBoard(obj)
            % Recursive function to solve the Sudoku puzzle
            for i = 1:obj.boardSize^2
                if mod(i,obj.boardSize) == 0
                    disp('----------------');
                end
                num = getNumberToPlace(obj,i);
                if num > 0
                    placeNumber(obj, i, num);
                    obj.solveBoard();
                    if not(obj.hasSolution())
                        backtrack(obj, i);
                    else
                        return;
                    end
                else
                    backtrack(obj, i);
                end
            end
        end
        
        function hasSolution(obj)
            % Check if the Sudoku puzzle has a solution
            for i = 1:obj.boardSize^2
                num = getNumberToPlace(obj,i);
                if num == 0
                    return;
                end
            end
            disp('Sudoku Puzzle Solved!');
            return true;
        end
        
        function placeNumber(obj, i, num)
            % Place the number in the Sudoku board
            row = ceil(i/obj.boardSize);
            col = mod(i,obj.boardSize);
            obj.solvedBoard(row,col) = num;
            obj.board(i) = 0;
        end
        
        function backtrack(obj, i)
            % Backtrack to previous position if no solution found
            for j = 1:9
                if isSafe(obj,i,j)
                    placeNumber(obj, i, j);
                    obj.solveBoard();
                    if obj.hasSolution()
                        return;
                    else
                        backtrack(obj, i);
                    end
                end
            end
        end
        
        function num = getNumberToPlace(obj, i)
            % Get the next number to place in the Sudoku board
            row = ceil(i/obj.boardSize);
            col = mod(i,obj.boardSize);
            for j = 1:9
                if obj.solvedBoard(row,col) == 0
                    return j;
                end
            end
        end
        
        function isSafe(obj, i, num)
            % Check if it's safe to place the number in the Sudoku board
            row = ceil(i/obj.boardSize);
            col = mod(i,obj.boardSize);
            for k = 1:9
                if obj.solvedBoard(row,k) == num || ...
                   obj.solvedBoard(k,col) == num || ...
                   obj.solvedBoard(row,col) == num
                    return false;
                end
            end
            startRow = (row-1)*obj.boardSize + 1;
            endRow = row*obj.boardSize;
            for j = startRow:endRow
                if obj.solvedBoard(j,col) == num
                    return false;
                end
            end
            startCol = (col-1)*9 + 1;
            endCol = col*9;
            for k = startCol:endCol
                if obj.solvedBoard(row,k) == num
                    return false;
                end
            end
            return true;
        end
    end
    
end

% Example usage
boardSize = 3;
board = [5,3,0,7,0,0,0,0,0;6,0,0,1,9,5,0,0,0;0,9,8,0,0,0,0,6,0];
sudokuSolver = SudokuSolver(boardSize);
sudokuSolver.solveSudoku(board);

% Display the solved board
disp('Solved Board:');
disp(sudokuSolver.solvedBoard);