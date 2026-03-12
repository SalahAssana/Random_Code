% Game of Life Simulation
% Author: [Your Name]

% Define constants
LIFE = 1;
DEATH = 0;

% Define function to count neighbors
function n = count_neighbors(board, i, j)
    n = 0;
    for k = -1:2
        for l = -1:2
            if (k == 0) && (l == 0), continue; % Skip the cell itself
            if (i + k >= size(board, 1)) || (j + l >= size(board, 2)), continue;
            n = n + board(i+k,j+l);
        end
    end
end

% Define function to evolve the game
function board = evolve(board)
    new_board = zeros(size(board));
    for i = 1:size(board, 1)
        for j = 1:size(board, 2)
            n = count_neighbors(board, i, j);
            if (board(i,j) == LIFE && (n < 2 || n > 3)) 
                new_board(i,j) = DEATH; % Underpopulation or overpopulation
            elseif (board(i,j) == DEATH && n == 3)
                new_board(i,j) = LIFE; % Revival by reproduction
            else
                new_board(i,j) = board(i,j); % Stay alive
            end
        end
    end
    return board;
end

% Define function to visualize the game
function visualize(board, title)
    imagesc(board);
    colorbar;
    set(gca,'XTick',1:size(board,2));
    set(gca,'YTick',1:size(board,1));
    xlabel('Columns');
    ylabel('Rows');
    title(title);
end

% Main script
if nargin < 1 || isempty(varargin{1})
    size_board = [30 30]; % Default board size
else
    size_board = varargin{1};
end

% Initialize the game with a random pattern
board = randi([0,1],size_board(1),size_board(2));

% Evolve and visualize the game
for i = 1:100
    board = evolve(board);
    if mod(i,10) == 0
        title_str = sprintf('Generation %d',i);
        visualize(board,title_str);
        pause(0.5); % Pause for 0.5 seconds between generations
    end
end