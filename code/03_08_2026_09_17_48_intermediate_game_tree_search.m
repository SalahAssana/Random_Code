% Game Tree Search
%
% A program that uses a depth-first search algorithm to find the best moves 
% in a game like chess or tic-tac-toe.

function tree_search
    % Define the game board as an array
    board = zeros(3, 3);

    % Define the possible moves (up, down, left, right)
    moves = {'up', 'down', 'left', 'right'};

    % Define a function to check if a move is valid
    function isValidMove(board, direction)
        switch(direction)
            case 'up'
                if board(1, :) == 0
                    return true;
                else
                    return false;
                end
            case 'down'
                if board(3, :) == 0
                    return true;
                else
                    return false;
                end
            case 'left'
                if board(:, 1) == 0
                    return true;
                else
                    return false;
                end
            case 'right'
                if board(:, 3) == 0
                    return true;
                else
                    return false;
                end
        end
    end

    % Define a function to make a move on the board
    function makeMove(board, direction)
        switch(direction)
            case 'up'
                for i = 1:3
                    if board(i, :) == 0
                        board(i, 1) = 1;
                        return;
                    end
                end
            case 'down'
                for i = 3:-1:1
                    if board(i, :) == 0
                        board(i, 3) = 1;
                        return;
                    end
                end
            case 'left'
                for i = 1:3
                    if board(:, i) == 0
                        board(1, i) = 1;
                        return;
                    end
                end
            case 'right'
                for i = 3:-1:1
                    if board(:, i) == 0
                        board(3, i) = 1;
                        return;
                    end
                end
        end
    end

    % Define a function to evaluate the game state
    function evaluation = evaluateBoard(board)
        emptyCells = sum(sum(board == 0));
        if emptyCells > 0
            return -10; % If there are still empty cells, penalize the current player
        else
            return 10; % If no more moves left, reward the current player
        end
    end

    % Define a function to perform the depth-first search
    function bestMove = dfs(board, depth, alpha, beta)
        if depth == 0 || sum(sum(board == 0)) == 0
            return evaluation(board); % If at the leaf node or no more moves left, evaluate the board
        end

        bestMove = -100;
        for i = 1:4
            move = moves{i};
            if isValidMove(board, move)
                makeMove(board, move);
                tempBestMove = dfs(board, depth - 1, alpha, beta);
                if tempBestMove > bestMove
                    bestMove = tempBestMove;
                end

                % Pruning: If the current move is worse than the alpha value, skip further exploration
                if bestMove >= beta
                    return bestMove;
                end

                makeMove(board, 'undo'); % Undo the move to backtrack
            end
        end

        % Pruning: If the current node's evaluation is better than the beta value, prune the subtree
        if bestMove <= alpha
            return bestMove;
        end
    end

    % Perform the depth-first search and find the best initial move
    bestInitialMove = -100;
    for i = 1:4
        board = zeros(3, 3);
        makeMove(board, moves{i});
        bestInitialMove = max(bestInitialMove, dfs(board, 2, -100, 100));
        makeMove(board, 'undo'); % Undo the move to backtrack
    end

    disp('The best initial move is: ');
    switch bestInitialMove
        case 10
            disp('No more moves left');
        case -10
            disp('There are still empty cells');
        otherwise
            disp(['The best move is ', moves{bestInitialMove+1}]);
    end
end

tree_search;