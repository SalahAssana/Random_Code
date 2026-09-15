% Random Walk Simulation
% Simulate random walks on a grid, illustrating fundamental concepts of probability and statistics

% Initialize variables
num_walks = 1000; % number of random walks to simulate
grid_size = 10; % size of the grid
steps_per_walk = 20; % number of steps per walk
start_position = [5 5]; % starting position of each walk

% Create a 2D array to store the final positions of the walks
final_positions = zeros(grid_size, grid_size);

% Simulate random walks and record final positions
for i = 1:num_walks
    current_position = start_position;
    for j = 1:steps_per_walk
        % Randomly choose a direction (up, down, left, right)
        direction = randi([1 4], 1);
        
        if direction == 1 && current_position(2) < grid_size
            current_position(2) = current_position(2) + 1;
        elseif direction == 2 && current_position(2) > 1
            current_position(2) = current_position(2) - 1;
        elseif direction == 3 && current_position(1) > 1
            current_position(1) = current_position(1) - 1;
        elseif direction == 4 && current_position(1) < grid_size
            current_position(1) = current_position(1) + 1;
        end
        
        % Record the final position of this walk
        if j == steps_per_walk
            final_positions(current_position(1), current_position(2)) = final_positions(current_position(1), current_position(2)) + 1;
        end
    end
end

% Display the final positions as a heatmap
imagesc(final_positions);
colormap gray;
colorbar;