% Simple Game of Life in MATLAB

% Initialize the game board (2D array)
board = zeros(10, 10);

% Set initial conditions
board(3:6, 3:6) = 1;

% Define the rules for the Game of Life
function nextBoard = evolve(board)
    [rows, cols] = size(board);
    nextBoard = zeros(rows, cols);
    
    % Iterate over each cell in the board
    for i = 1:rows
        for j = 1:cols
            % Count the number of live neighbors
            liveNeighbors = 0;
            for k = -1:1
                for l = -1:1
                    if abs(k) + abs(l) > 0 && ...
                            i+k <= rows && i+k >= 1 && j+l <= cols && j+l >= 1 && ...
                            board(i+k, j+l)
                        liveNeighbors = liveNeighbors + 1;
                    end
                end
            end
            
            % Apply the rules of the Game of Life
            if board(i, j) == 1 && (liveNeighbors < 2 || liveNeighbors > 3)
                nextBoard(i, j) = 0;  % Underpopulation or overpopulation: die
            elseif board(i, j) == 0 && liveNeighbors == 3
                nextBoard(i, j) = 1;  % Reproduction: birth
            else
                nextBoard(i, j) = board(i, j);  % Stay the same
            end
        end
    end
end

% Evolve the game board over time
for generation = 1:10
    board = evolve(board);
    pause(0.5);  % Pause for a short time to visualize the evolution
    clf;  % Clear the current figure
    imagesc(board);  % Display the current state of the game board
    axis off;  % Turn off the axis
end