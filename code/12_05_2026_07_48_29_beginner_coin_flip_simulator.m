% Coin Flip Simulator

% Define the number of coin flips to simulate
num_flips = 1000;

% Initialize counters for heads and tails
heads = 0;
tails = 0;

% Simulate coin flips using random numbers
for i = 1:num_flips
    % Generate a random number between 0 and 1
    rand_num = rand();
    
    % If the number is less than 0.5, count it as heads
    if rand_num < 0.5
        heads = heads + 1;
    else
        tails = tails + 1;
    end
end

% Calculate the probability of heads and tails
heads_prob = heads / num_flips;
tails_prob = tails / num_flips;

% Display the results
fprintf('Heads: %d (%.2f%%)\n', heads, heads_prob*100);
fprintf('Tails: %d (%.2f%%)\n', tails, tails_prob*100);