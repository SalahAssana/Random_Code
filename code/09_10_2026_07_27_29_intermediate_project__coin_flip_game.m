% Project: Coin Flip Game
% Description: Simulates flipping coins and keeps track of heads and tails.

% Initialize variables to store results
heads = 0;
tails = 0;

% Function to simulate a coin flip
function [result, heads, tails] = flipCoin(heads, tails)
    result = randi([0,1], 1);
    
    if result == 1
        heads = heads + 1;
    else
        tails = tails + 1;
    end
    
end

% Main script
for i = 1:100 % Flip the coin 100 times
    [result, heads, tails] = flipCoin(heads, tails);
    
    if mod(i,10) == 0 && i > 0
        fprintf('Heads: %d, Tails: %d\n', heads, tails);
    end
end

fprintf('Final Results: Heads: %d, Tails: %d\n', heads, tails);