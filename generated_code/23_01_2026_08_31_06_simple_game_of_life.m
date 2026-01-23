% Simple Game of Life in MATLAB

% Initialize grid size and state
grid_size = 10;
grid_state = zeros(grid_size);

% Initial state (randomly set some cells to 1)
for i = 1:grid_size
    for j = 1:grid_size
        if rand < 0.2
            grid_state(i, j) = 1;
        end
    end
end

% Define Game of Life rules
function next_generation = game_of_life(grid_state, grid_size)
    next_generation = zeros(grid_size);
    
    for i = 1:grid_size
        for j = 1:grid_size
            % Count live neighbors
            live_neighbors = 0;
            for k = -1:1
                for l = -1:1
                    if (k == 0 && l == 0) || i + k < 1 || i + k > grid_size || j + l < 1 || j + l > grid_size
                        continue
                    end
                    if grid_state(i + k, j + l)
                        live_neighbors = live_neighbors + 1;
                    end
                end
            end
            
            % Apply Game of Life rules
            if grid_state(i, j) == 1 && (live_neighbors < 2 || live_neighbors > 3)
                next_generation(i, j) = 0;
            elseif grid_state(i, j) == 0 && live_neighbors == 3
                next_generation(i, j) = 1;
            else
                next_generation(i, j) = grid_state(i, j);
            end
        end
    end
end

% Run the game for 10 generations
for i = 1:10
    grid_state = game_of_life(grid_state, grid_size);
    
    % Print current state
    fprintf('Generation %d:\n', i);
    for j = 1:grid_size
        fprintf('%s\n', num2str(grid_state(j, :)));
    end
end