% Sudoku Solver using Backtracking Algorithm
function sudoku_solver(board)
    % Check input validity
    if size(board, 1) ~= size(board, 2)
        error('Input board is not a square');
    end
    
    % Function to check if number can be placed at given position
    function possible = is_possible(board, row, col, num)
        % Check row
        for i = 1:size(board, 2)
            if board(row, i) == num
                possible = false;
                return
            end
        end
        
        % Check column
        for i = 1:size(board, 1)
            if board(i, col) == num
                possible = false;
                return
            end
        end
        
        % Check box
        start_row = floor((row - 1) / size(board, 1));
        start_col = mod(col - 1, size(board, 1));
        
        for i = start_row*size(board, 1)+1:start_row*size(board, 1)+size(board, 1)
            for j = start_col+1:start_col+size(board, 1)
                if board(i, j) == num
                    possible = false;
                    return
                end
            end
        end
        
        possible = true;
    end
    
    % Function to solve Sudoku using backtracking algorithm
    function solved_board = solve_sudoku(board)
        for row = 1:size(board, 1)
            for col = 1:size(board, 2)
                if board(row, col) == 0
                    for num = 1:9
                        if is_possible(board, row, col, num)
                            board(row, col) = num;
                            solved_board = solve_sudoku(board);
                            if ~exist('solved_board', 'file')
                                return board;
                            end
                            board(row, col) = 0;
                    end
                    return
                end
            end
        end
        
        % If no more empty cells, Sudoku is solved
        solved_board = board;
    end
    
    % Solve Sudoku using backtracking algorithm
    solved_board = solve_sudoku(board);
    
    % Print the solved Sudoku board
    for row = 1:size(solved_board, 1)
        for col = 1:size(solved_board, 2)
            if solved_board(row, col) == 0
                disp('---');
            else
                fprintf('%d ', solved_board(row, col));
            end
        end
        disp('');
    end
end

% Example usage:
board = [5,3,'.',7,'.','.",".",6,''];
board(2,1) = 8;
board(4,4) = 4;

sudoku_solver(board);