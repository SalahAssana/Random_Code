% Coin Flip Simulation
% Simulate the flipping of a coin multiple times, keeping track of the number of heads and tails,
% and calculate the probability of getting a certain sequence of results.

heads = 0;
tails = 0;

numFlips = 100; % Number of coin flips to simulate

for i = 1:numFlips
    flipResult = rand < 0.5; % Randomly generate heads (1) or tails (0)
    
    if flipResult == 1
        heads = heads + 1;
    else
        tails = tails + 1;
    end
end

% Calculate the probability of getting a certain sequence of results
headProbability = heads / numFlips;
tailProbability = tails / numFlips;

fprintf('Heads: %d\n', heads);
fprintf('Tails: %d\n', tails);
fprintf('Head Probability: %.2f\n', headProbability);
fprintf('Tail Probability: %.2f\n', tailProbability);