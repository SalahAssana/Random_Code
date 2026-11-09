% Game AI Optimization for Tic-Tac-Toe

% Initialize game board as 3x3 array
board = zeros(3, 3);

% Define possible moves (0-8) and their corresponding board indices
moves = [0 1 2; 3 4 5; 6 7 8];

% Define winning combinations (rows, columns, diagonals)
winningCombinations = [
    1 2 3;
    4 5 6;
    7 8 9;
    1 5 9;
    3 5 7;
    1 4 7;
    2 5 8;
    ];

% Define minimax function to optimize AI's moves
function [bestMove, bestScore] = minimax(board, depth, isMaximizingPlayer)
    % Initialize best move and score
    bestMove = -1;
    bestScore = -inf;

    % Loop through all possible moves
    for i = 1:size(moves, 2)
        % Make a move on the board
        currentBoard = board;
        currentBoard(sub2ind(size(currentBoard), moves(1, i), moves(2, i))) = isMaximizingPlayer;

        % Check if the game has been won or drawn
        if any(any(ismember(currentBoard, winningCombinations)))
            % Evaluate score based on the winner (0 for draw, 1 for win)
            score = isMaximizingPlayer;
        elseif depth == 0
            % Evaluate score as a tie
            score = 0;
        else
            % Recursively call minimax with the next player
            if isMaximizingPlayer
                [newBestMove, newBestScore] = minimax(currentBoard, depth - 1, false);
            else
                [newBestMove, newBestScore] = minimax(currentBoard, depth - 1, true);
            end

            % Update best move and score
            if isMaximizingPlayer && newBestScore > bestScore
                bestMove = i;
                bestScore = newBestScore;
            elseif ~isMaximizingPlayer && newBestScore < bestScore
                bestMove = i;
                bestScore = newBestScore;
            end
        end
    end
end

% Define AI's main function to play the game
function aiPlayGame()
    % Initialize score and best move
    score = 0;
    bestMove = -1;

    % Loop until the game is won or drawn
    while true
        % Update board with AI's moves
        [bestMove, ~] = minimax(board, 5, true);

        % Make a move on the board
        currentBoard = board;
        currentBoard(sub2ind(size(currentBoard), moves(1, bestMove), moves(2, bestMove))) = 2;

        % Check if the game has been won or drawn
        if any(any(ismember(currentBoard, winningCombinations)))
            score = currentBoard(sub2ind(size(currentBoard), : , :));
            break;
        end

        % Update board for human's turn
        board(sub2ind(size(board), 1, 1)) = 1;

        % Check if the game has been won or drawn
        if any(any(ismember(board, winningCombinations)))
            score = board(sub2ind(size(board), : , :));
            break;
        end
    end

    % Print the final score
    disp(['AI wins with a score of ', num2str(score)]);
end

% Run the AI's main function to play the game
aiPlayGame();