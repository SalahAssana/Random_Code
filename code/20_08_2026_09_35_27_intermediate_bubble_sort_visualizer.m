% Bubble Sort Visualizer

% Import necessary libraries
import matplotlib.pyplot as plt
import numpy as np

% Define the bubble sort function
function sorted_array = bubble_sort(arr)
    n = length(arr);
    for i = 1:n-1
        swapped = false;
        for j = 1:n-i
            if arr(j) > arr(j+1)
                temp = arr(j);
                arr(j) = arr(j+1);
                arr(j+1) = temp;
                swapped = true;
            end
        end
        if ~swapped
            break;
        end
    end
    sorted_array = arr;
end

% Define the main function for visualization
function visualize_bubble_sort()
    % Initialize the figure and axis
    fig, ax = subplot(2,1,1);
    
    % Generate a random array
    arr = randi([0,100], 10, 1);
    
    % Visualize the original array
    plot(ax, arr, 'o');
    title('Original Array');
    drawnow;
    
    % Perform bubble sort on the array
    sorted_arr = bubble_sort(arr);
    
    % Visualize the sorted array
    plot(ax, sorted_arr, 'o');
    title('Sorted Array');
    drawnow;
end

% Run the main function for visualization
visualize_bubble_sort();