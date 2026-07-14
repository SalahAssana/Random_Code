% Coin Flip Simulator
% This program simulates the probability of getting different coin flip outcomes (heads, tails) based on the number of flips.

numFlips = 1000; % Number of coin flips to simulate
headsCount = zeros(1,11); % Initialize array to store count of heads for each possible outcome

for i = 1:11
    for j = 1:numFlips
        if rand < 0.5
            headsCount(i) = headsCount(i) + 1;
        end
    end
end

% Calculate the probability of getting 'i' number of heads
probability = zeros(1,11);
for i = 1:11
    probability(i) = (headsCount(i)/numFlips)*100; % Convert to percentage
end

% Display the results
fprintf('Number of Heads\tProbability\n');
for i = 1:11
    fprintf('%d\t%.2f%%\n', i, probability(i));
end