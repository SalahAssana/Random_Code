% Sudoku Solver using Dancing Links Algorithm
%
% This script solves Sudoku puzzles by implementing the Dancing Links algorithm.

% Define structure to represent Sudoku board and constraints
struct sudoku_board;

sudoku_board.rows = 9;
sudoku_board.cols = 9;
sudoku_board.values = zeros(sudoku_board.rows, sudoku_board.cols);

sudoku_board.constraints = struct('row', [], 'col', []);

function solve_sudoku(board)
    % Function to solve Sudoku puzzle using Dancing Links algorithm
    %
    % This function iterates over each empty cell in the board and tries to place a number.
    % If placement is valid, it recursively calls itself with updated board. If not,
    % it backtracks by removing the last placed number.

    if any(any(board.values == 0))
        % Find next empty cell
        [i, j] = find(board.values == 0);
        i = i(1); j = j(1);

        for num = 1:9
            board.values(i, j) = num;

            % Check if placement is valid (row and column constraints)
            if all(any(board.values(:,j) ~= num)) && all(any(board.values(i,:) ~= num))
                % If valid, recursively call solve_sudoku with updated board
                solve_sudoku(board);

                % Backtrack by removing the last placed number
                if any(any(board.values == num))
                    [k, l] = find(board.values == num);
                    k = k(1); l = l(1);
                    board.values(k, l) = 0;
                end
            end
        end
    else
        % If no empty cells left, print the solved board
        fprintf('Sudoku puzzle solved:\n');
        for i = 1:9
            fprintf('%d ', board.values(i,:));
            if mod(i,3) == 0 && i ~= 9
                fprintf('\n');
            end
        end
    end
end

% Initialize Sudoku board with given values (0 means empty cell)
board = sudoku_board;
board.values([1,2,3],:) = [5,3,7;6,7,8;4,9,2];
board.values(:,[1,2,3]) = [7,8,9;5,1,4;3,6,2];

% Solve Sudoku puzzle
solve_sudoku(board);