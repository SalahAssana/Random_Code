% Sudoku Solver
% Author: Your Name
% Description: A backtracking algorithm to solve Sudoku puzzles

function [solved_board] = sudoku_solver(board)
    % Function to check if a given number can be placed in a cell
    function valid_move = is_valid_move(board, row, col, num)
        for i = 1:9
            if board(row,i) == num
                valid_move = false;
                return
            end
        end
        
        for i = 1:9
            if board(i,col) == num
                valid_move = false;
                return
            end
        end
        
        box_row = floor((row-1)/3)*3 + 1;
        box_col = floor((col-1)/3)*3 + 1;
        
        for i = box_row:box_row+2
            for j = box_col:box_col+2
                if board(i,j) == num
                    valid_move = false;
                    return
                end
            end
        end
        
        valid_move = true;
    end

    % Function to solve the Sudoku puzzle using backtracking
    function solved_board = backtrack(board)
        for row = 1:9
            for col = 1:9
                if board(row,col) == 0
                    for num = 1:9
                        if is_valid_move(board, row, col, num)
                            board(row,col) = num;
                            
                            % Recursively call the backtrack function
                            temp_board = board;
                            solved_board = backtrack(temp_board);
                            
                            % If a solution is found, return it
                            if ~isempty(solved_board)
                                return
                            end
                            
                            % If no solution is found, backtrack and try another number
                            board(row,col) = 0;
                        end
                    end
                    
                    % If all numbers have been tried and none work, the puzzle has no solution
                    if row == 9
                        solved_board = [];
                        return
                    end
                end
            end
        end
        
        % Return the solved board
        solved_board = board;
    end

    % Solve the Sudoku puzzle using backtracking
    temp_board = board;
    solved_board = backtrack(temp_board);
end

% Main function to generate and solve a Sudoku puzzle
function main()
    % Generate a random Sudoku puzzle
    row1 = randi([0,9], 1, 81);
    board = reshape(row1, 9, 9);

    % Solve the Sudoku puzzle using backtracking
    solved_board = sudoku_solver(board);

    % Display the original and solved boards
    figure;
    for i = 1:9
        subplot(3,3,i);
        if i <= 8
            imagesc(fliplr(board(:,i)));
            axis off;
            axis equal;
            colormap(gray);
        else
            imagesc(fliplr(solved_board));
            axis off;
            axis equal;
            colormap(gray);
        end
    end

    % Ask the user to input a new Sudoku puzzle or exit the program
    prompt = 'Enter a command (S to solve, E to exit): ';
    choice = input(prompt,'s');

    while choice == 'S'
        % Generate and solve another Sudoku puzzle
        row1 = randi([0,9], 1, 81);
        board = reshape(row1, 9, 9);

        solved_board = sudoku_solver(board);

        figure;
        for i = 1:9
            subplot(3,3,i);
            if i <= 8
                imagesc(fliplr(board(:,i)));
                axis off;
                axis equal;
                colormap(gray);
            else
                imagesc(fliplr(solved_board));
                axis off;
                axis equal;
                colormap(gray);
            end
        end

        prompt = 'Enter a command (S to solve, E to exit): ';
        choice = input(prompt,'s');
    end

    if choice == 'E'
        disp('Exiting the program.');
    else
        error('Invalid command. Exiting the program.');
    end
end

main();