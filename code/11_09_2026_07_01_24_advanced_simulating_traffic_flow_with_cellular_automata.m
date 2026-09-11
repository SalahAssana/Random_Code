% Simulating Traffic Flow with Cellular Automata
% Advanced Complexity Project

classdef TrafficCell < handle
    properties
        speed;  % vehicle speed (0-1)
        position;  % current position on grid (0-100)
    end
    
    methods
        function obj = TrafficCell(speed, position)
            obj.speed = speed;
            obj.position = position;
        end
        
        function move(obj, gridSize)
            if rand < obj.speed  % random movement based on speed
                obj.position = mod(obj.position + 1, gridSize);
            end
        end
    end
end

classdef TrafficFlow < handle
    properties
        cells;  % array of TrafficCell objects
        gridSize;  % size of the grid (0-100)
        speedLimit;  % maximum allowed speed (0-1)
    end
    
    methods
        function obj = TrafficFlow(gridSize, speedLimit)
            obj.gridSize = gridSize;
            obj.speedLimit = speedLimit;
            obj.cells = zeros(1, gridSize);
        end
        
        function simulate(obj, numSteps)
            for i = 1:numSteps
                % update each cell based on its neighbors and speed limit
                for j = 1:obj.gridSize
                    if obj.cells(j) > 0
                        cell = obj.cells(j);
                        if rand < cell.speed  % random movement based on speed
                            newCellPosition = mod(cell.position + 1, obj.gridSize);
                            if newCellPosition == 0 && rand < 0.5  % boundary condition: vehicles can enter from the right side with probability 0.5
                                newSpeed = min(rand, cell.speed * 2);  % random speed adjustment for entering vehicles
                            elseif newCellPosition > 0 && rand < 0.1  % boundary condition: vehicles can exit from the left side with probability 0.1
                                newSpeed = max(0, cell.speed - rand);
                            else
                                newSpeed = cell.speed;
                            end
                            obj.cells(newCellPosition) = TrafficCell(min(obj.speedLimit, newSpeed), newCellPosition);
                        end
                    end
                end
            end
        end
        
        function visualize(obj)
            % create a plot of the traffic flow over time
            figure;
            for i = 1:obj.gridSize
                bar([i], obj.cells(i).speed * ones(1, numSteps));
            end
            xlabel('Position on Grid');
            ylabel('Speed');
        end
    end
end

% create a TrafficFlow object with default parameters and simulate traffic flow
trafficFlow = TrafficFlow(100, 0.5);
trafficFlow.simulate(100);

% visualize the traffic flow over time
trafficFlow.visualize();