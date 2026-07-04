% Random Walk Simulation
clear; clc;

% Number of steps in the random walk
numSteps = 1000;

% Initialize the current position at the origin (0, 0)
x = 0;
y = 0;

% Initialize arrays to store the x and y positions over time
xPos = zeros(1, numSteps);
yPos = zeros(1, numSteps);

% Simulate the random walk
for i = 1:numSteps
    % Randomly choose a direction (north, south, east, or west)
    direction = randi([1, 4], 1);
    
    switch direction
        case 1
            y = y + 1;
        case 2
            y = y - 1;
        case 3
            x = x + 1;
        case 4
            x = x - 1;
    end
    
    % Store the current position in the arrays
    xPos(i) = x;
    yPos(i) = y;
end

% Calculate the average distance from the origin over time
avgDist = sum(sqrt((xPos-x).^2 + (yPos-y).^2)) / numSteps;

% Display the results
fprintf('Average distance from the origin: %f\n', avgDist);