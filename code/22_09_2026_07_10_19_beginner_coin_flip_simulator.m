% Coin Flip Simulator
% This script simulates flipping a coin multiple times and displays the results.

% Set the number of flips
numFlips = 100;

% Initialize the count of heads and tails
headsCount = 0;
tailsCount = 0;

% Simulate the coin flip
for i = 1:numFlips
    % Randomly decide whether to flip a head or tail
    if rand < 0.5
        headsCount = headsCount + 1;
    else
        tailsCount = tailsCount + 1;
    end
end

% Display the results
fprintf('Heads: %d\n', headsCount);
fprintf('Tails: %d\n', tailsCount);

% Calculate and display the percentage of heads
headsPercentage = (headsCount / numFlips) * 100;
fprintf('Heads Percentage: %.2f %%\n', headsPercentage);

% Calculate and display the percentage of tails
tailsPercentage = (tailsCount / numFlips) * 100;
fprintf('Tails Percentage: %.2f %%\n', tailsPercentage);