% Sorting Visualizer
% Author: [Your Name]
% Date: 2021-02-20
%
% Description:
%   Visualizes different sorting algorithms such as bubble sort,
%   selection sort, and insertion sort using MATLAB graphics.

% Define the maximum number of elements in the array
max_elements = 100;

% Define the initial random array
array = randi([1 max_elements], 1, max_elements);

% Define the figure handle for visualization
figure_handle = figure('Name', 'Sorting Visualizer');

% Define the subplots for each sorting algorithm
subplot_handles = cell(3, 2);
for i = 1:3
    subplot_handles{i, 1} = subplot(1, 2, i);
    title(subplot_handles{i, 1}, ['Sorting Algorithm ', num2str(i)]);
end

% Define the function to generate a bar chart
function plot_array(array)
    bar(array);
    xlabel('Index');
    ylabel('Value');
    grid on;
end

% Define the bubble sort algorithm
function array = bubble_sort(array)
    n = length(array);
    for i = 1:n-1
        for j = 1:n-i
            if array(j) > array(j + 1)
                temp = array(j);
                array(j) = array(j+1);
                array(j+1) = temp;
            end
        end
    end
end

% Define the selection sort algorithm
function array = selection_sort(array)
    n = length(array);
    for i = 1:n-1
        min_index = i;
        for j = i+1:n
            if array(j) < array(min_index)
                min_index = j;
            end
        end
        temp = array(i);
        array(i) = array(min_index);
        array(min_index) = temp;
    end
end

% Define the insertion sort algorithm
function array = insertion_sort(array)
    n = length(array);
    for i = 2:n
        key = array(i);
        j = i-1;
        while j >= 1 && array(j) > key
            array(j + 1) = array(j);
            j = j - 1;
        end
        array(j+1) = key;
    end
end

% Main script
for i = 1:3
    array_copy = array;
    switch i
        case 1
            array_copy = bubble_sort(array_copy);
        case 2
            array_copy = selection_sort(array_copy);
        case 3
            array_copy = insertion_sort(array_copy);
    end
    subplot_handles{i, 1};
    plot_array(array_copy);
end

% Display the figure
figure_handle;