% Game of Life Simulation
% Author: [Your Name]

function game_of_life = simulate_game_of_life(initial_state, generations)
    % Initialize the game state
    [rows, cols] = size(initial_state);
    game_of_life = initial_state;

    for i = 1:generations
        % Create a temporary array to hold the new state
        temp_state = zeros(rows, cols);

        % Iterate over each cell in the grid
        for j = 1:rows
            for k = 1:cols
                % Count the number of live neighbors
                num_neighbors = count_neighbors(game_of_life, j, k);
                if game_of_life(j,k) == 1 && (num_neighbors < 2 || num_neighbors > 3)
                    temp_state(j,k) = 0; % Die from underpopulation or overpopulation
                elseif game_of_life(j,k) == 0 && num_neighbors == 3
                    temp_state(j,k) = 1; % Birth from neighboring cells
                else
                    temp_state(j,k) = game_of_life(j,k); % Stay the same
                end
            end
        end

        % Update the game state for the next generation
        game_of_life = temp_state;
    end
end

function num_neighbors = count_neighbors(state, row, col)
    % Count the number of live neighbors
    rows = size(state, 1);
    cols = size(state, 2);

    num_neighbors = 0;

    for i = -1:1
        for j = -1:1
            if (i == 0 && j == 0) || row + i < 1 || row + i > rows || col + j < 1 || col + j > cols
                continue;
            end

            num_neighbors = num_neighbors + state(row+i, col+j);
        end
    end

    num_neighbors = mod(num_neighbors, 2); % Remove the cell itself from the count
end

% Test the function
initial_state = [0 1 0; 0 0 1; 1 1 1];
game_of_life = simulate_game_of_life(initial_state, 10);