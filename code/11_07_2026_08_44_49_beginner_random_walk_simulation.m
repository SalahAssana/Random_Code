% Random Walk Simulation in 2D space
% Authors: [Your Name], [Date]
% Complexity Level: BEGINNER

% Import necessary libraries
import java.awt.*

% Define constants for simulation parameters
numParticles = 10; % number of particles to simulate
numSteps = 100; % number of steps per particle
probabilities = [0.5, 0.3, 0.2]; % probabilities for different directions

% Initialize plot and axis
figure;
axis equal;

% Simulate random walks and plot the paths
for i = 1:numParticles
    x(i) = 0; y(i) = 0; % initialize particle position
    direction = randi([1, size(probabilities,2)]); % choose a direction based on probability
    for j = 1:numSteps
        if direction == 1 && rand < probabilities(1)
            x(i) = x(i) + 1; y(i) = y(i);
        elseif direction == 2 && rand < probabilities(2)
            x(i) = x(i); y(i) = y(i) + 1;
        else
            x(i) = x(i); y(i) = y(i);
        end
    end
    plot(x(i), y(i), 'o');
end

% Show the plot
title('Random Walk Simulation');
xlabel('X-Axis');
ylabel('Y-Axis');