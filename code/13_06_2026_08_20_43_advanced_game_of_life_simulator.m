% Game of Life Simulator in MATLAB

classdef GameOfLife
    methods
        function obj = GameOfLife(gridSize)
            % Initialize grid with random values (0s and 1s)
            obj.grid = zeros(gridSize, gridSize);
            for i = 1:gridSize
                for j = 1:gridSize
                    if rand < 0.5
                        obj.grid(i, j) = 1;
                    end
                end
            end
            
            % Set grid boundary conditions (wraparound)
            obj.grid(:, 1) = obj.grid(:, end);
            obj.grid(end, :) = obj.grid(1, :);
        end
        
        function displayGrid(obj)
            % Display the current state of the grid using 'o' for alive cells and '.' for dead cells
            clc;
            for i = 1:size(obj.grid, 1)
                for j = 1:size(obj.grid, 2)
                    if obj.grid(i, j) == 1
                        fprintf('o ');
                    else
                        fprintf('. ');
                    end
                end
                fprintf('\n');
            end
        end
        
        function obj = nextGeneration(obj)
            % Compute the next generation of the Game of Life using the cellular automata rules
            newGrid = zeros(size(obj.grid));
            for i = 1:size(obj.grid, 1)
                for j = 1:size(obj.grid, 2)
                    liveNeighbors = 0;
                    for k = -1:1
                        for l = -1:1
                            if (k == 0 && l == 0) || abs(k) + abs(l) > 1
                                continue;
                            end
                            if obj.grid(i+k, j+l) == 1
                                liveNeighbors = liveNeighbors + 1;
                            end
                        end
                    end
                    
                    % Apply the Game of Life rules
                    if obj.grid(i, j) == 1 && (liveNeighbors < 2 || liveNeighbors > 3)
                        newGrid(i, j) = 0;  % Underpopulation or overpopulation: cell dies
                    elseif obj.grid(i, j) == 0 && liveNeighbors == 3
                        newGrid(i, j) = 1;  % Reproduction: cell becomes alive
                    else
                        newGrid(i, j) = obj.grid(i, j);  % Cell remains in the same state
                    end
                end
            end
            
            % Update the grid for the next generation
            obj.grid = newGrid;
        end
    end
    
    methods (Static)
        function runSimulation(gridSize, generations)
            % Create a Game of Life object with the specified grid size
            game = GameOfLife(gridSize);
            
            % Run the simulation for the specified number of generations
            for i = 1:generations
                game.displayGrid();
                game.nextGeneration();
                pause(0.5);  % Pause for visualization purposes
            end
        end
    end
end

% Run the simulation with a grid size of 20 and 10 generations
GameOfLife.runSimulation(20, 10);