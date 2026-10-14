% Game of Life Simulator
%
% This program simulates the Game of Life, a cellular automaton created by Conway,
% using arrays and loops to update generations.

function game_of_life()
    % Initialize the grid size (e.g., 20x20)
    N = 20;
    
    % Create a random initial state for the grid
    grid = randi([0,1], N, N);
    
    % Define the number of generations to simulate
    num_generations = 10;
    
    % Run the simulation
    for i = 1:num_generations
        % Calculate the next generation based on the current state
        next_grid = game_of_life_update(grid);
        
        % Print the current grid state (optional)
        if mod(i, 2) == 0
            disp(next_grid);
        end
        
        % Update the grid for the next iteration
        grid = next_grid;
    end
    
    % Print the final grid state
    disp(grid);
end

function grid_next = game_of_life_update(grid)
    % Define the rules of the Game of Life:
    % 1. Any live cell with fewer than two live neighbors dies (underpopulation).
    % 2. Any live cell with two or three live neighbors lives on to the next generation.
    % 3. Any live cell with more than three live neighbors dies (overpopulation).
    % 4. Any dead cell with exactly three live neighbors becomes a live cell (reproduction).

    % Get the number of rows and columns in the grid
    [rows, cols] = size(grid);
    
    % Create the next generation grid filled with zeros
    grid_next = zeros(rows, cols);
    
    for i = 1:rows
        for j = 1:cols
            % Count the live neighbors (excluding the cell itself)
            live_neighbors = 0;
            for k = max(1, i-1):min(i+1, rows)
                for l = max(1, j-1):min(j+1, cols)
                    if k ~= i || l ~= j
                        if grid(k, l) == 1
                            live_neighbors = live_neighbors + 1;
                        end
                    end
                end
            end
            
            % Apply the Game of Life rules based on the cell's state and neighbors
            if grid(i, j) == 1
                if live_neighbors < 2 || live_neighbors > 3
                    grid_next(i, j) = 0;
                else
                    grid_next(i, j) = 1;
                end
            elseif live_neighbors == 3
                grid_next(i, j) = 1;
            end
        end
    end
end

% Run the simulation if this script is executed as the main program
if nargin == 0
    game_of_life();
end