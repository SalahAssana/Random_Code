% Game of Life Simulator
% Author: [Your Name]

function game_of_life_simulator
    % Initialize grid size
    rows = 20;
    cols = 20;

    % Initialize grid with random values (0s and 1s)
    grid = randi([0, 1], rows, cols);

    % Set the initial pattern
    grid(5:10, :) = 1;  % Vertical line
    grid(:, 5:10) = 1;   % Horizontal line

    % Show the initial state of the grid
    figure;
    imagesc(grid);
    colormap(gray);
    axis off;

    for generation = 1:100
        % Calculate the next state of each cell
        next_grid = zeros(rows, cols);

        for i = 2:rows-1
            for j = 2:cols-1
                neighbors = grid(i-1:i+1, j-1:j+1);
                live_neighbors = sum(neighbors(:));
                if grid(i, j) == 1 && (live_neighbors < 2 || live_neighbors > 3)
                    next_grid(i, j) = 0;  % Cell dies
                elseif grid(i, j) == 0 && live_neighbors == 3
                    next_grid(i, j) = 1;  % Cell is born
                else
                    next_grid(i, j) = grid(i, j);
                end
            end
        end

        % Update the grid
        grid = next_grid;

        % Show the state of the grid after each generation
        figure;
        imagesc(grid);
        colormap(gray);
        axis off;
    end
end