% Array Search Algorithm - Binary Search Implementation

% Define a function to perform binary search on an array
function index = binarySearch(arr, target)
    low = 1;
    high = length(arr);
    
    while low <= high
        mid = (low + high) / 2;
        
        if arr(mid) == target
            index = mid;
            return
        elseif arr(mid) < target
            low = mid + 1;
        else
            high = mid - 1;
        end
    end
    
    % If the target is not found, return -1
    index = -1;
end

% Generate synthetic data for testing
data = [5, 7, 12, 15, 18, 20, 22, 25];
target_values = [7, 15, 20];

% Search for each target value and display the results
for i = 1:length(target_values)
    index = binarySearch(data, target_values(i));
    
    if index == -1
        fprintf('Target %d not found in array.\n', target_values(i));
    else
        fprintf('Target %d found at index %d.\n', target_values(i), index);
    end
end