% Coin Flip Simulator
%
% Simulate the probability of getting a certain number of heads or tails in a coin flip experiment.

% Define the number of flips (experiments)
numFlips = 10000;

% Initialize variables to store the results
headsCount = zeros(1,11);
tailsCount = zeros(1,11);

% Loop through each flip
for i=1:numFlips
    % Generate a random number between 0 and 1
    flipResult = rand;
    
    % If the result is less than or equal to 0.5, it's heads (1)
    if flipResult <= 0.5
        % Increment the corresponding count in the heads array
        headsCount(ceil(i/1000)) = headsCount(ceil(i/1000)) + 1;
    else
        % Otherwise, it's tails (0) and increment the tails count
        tailsCount(ceil(i/1000)) = tailsCount(ceil(i/1000)) + 1;
    end
end

% Calculate the probability of each result
headsProb = headsCount ./ numFlips;
tailsProb = tailsCount ./ numFlips;

% Display the results
fprintf('Heads Probability: \n');
for i=1:length(headsProb)
    fprintf(['After ', num2str(1000*i), ' flips, the probability of getting heads is approximately ', ...
        num2str(round(headsProb(i)*100)), '%\n']);
end

fprintf('\nTails Probability: \n');
for i=1:length(tailsProb)
    fprintf(['After ', num2str(1000*i), ' flips, the probability of getting tails is approximately ', ...
        num2str(round(tailsProb(i)*100)), '%\n']);
end