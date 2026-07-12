% Coin Flip Simulator
% Author: [Your Name]

% Initialize variables to track statistics
heads = 0;
tails = 0;
streak_length = 0;

for i = 1:100 % Simulate 100 coin flips
    flip = randi([0, 1]); % Generate random outcome (0 for tails, 1 for heads)
    
    if flip == 1
        heads = heads + 1; % Update heads count
    else
        tails = tails + 1; % Update tails count
        
        if streak_length > 0
            streak_length = 0; % Reset streak length when tails is flipped
        end
    else
        streak_length = streak_length + 1; % Increase streak length for consecutive heads
    end
    
    % Display current statistics every 10 flips
    if mod(i, 10) == 0
        fprintf('Heads: %d, Tails: %d, Streak Length: %d\n', heads, tails, streak_length);
    end
end

% Display final statistics
fprintf('Final Statistics:\n');
fprintf('Heads: %d, Tails: %d, Streak Length: %d\n', heads, tails, streak_length);