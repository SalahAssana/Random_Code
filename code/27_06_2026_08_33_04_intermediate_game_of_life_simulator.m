% Game of Life Simulator
%
% A cellular automaton simulation using parallel processing techniques.

function game_of_life
    % Define the size of the grid
    N = 100;
    grid_size = [N, N];
    
    % Initialize the grid with random values (0 or 1)
    grid = randi([0, 1], grid_size);
    
    % Define the rules for the Game of Life
    function next_generation = update(grid)
        next_generation = zeros(size(grid));
        
        for i = 1:N
            for j = 1:N
                neighbors = get_neighbors(grid, i, j);
                alive_neighbors = sum(neighbors(:));
                
                if grid(i, j) == 1
                    % If a cell is alive and has exactly two or three alive neighbors,
                    % it remains alive.
                    if alive_neighbors >= 2 && alive_neighbors <= 3
                        next_generation(i, j) = 1;
                    end
                else
                    % If a cell is dead and has exactly three alive neighbors,
                    % it becomes alive.
                    if alive_neighbors == 3
                        next_generation(i, j) = 1;
                    end
                end
            end
        end
    end
    
    function neighbors = get_neighbors(grid, i, j)
        neighbors = zeros(3, 3);
        
        for k = -1:1
            for l = -1:1
                if (k == 0) && (l == 0)
                    continue;
                
                new_i = i + k;
                new_j = j + l;
                
                if (new_i >= 1) && (new_i <= N) && (new_j >= 1) && (new_j <= N)
                    neighbors(k+2, l+2) = grid(new_i, new_j);
                end
            end
        end
    end
    
    % Run the simulation for a specified number of generations
    num_generations = 10;
    
    for i = 1:num_generations
        grid = update(grid);
        
        if mod(i, 2) == 0
            disp('Generation:');
            disp(grid);
            pause(0.5);
        end
    end
end

game_of_life();