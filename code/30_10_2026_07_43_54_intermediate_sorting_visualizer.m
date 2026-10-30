% Sorting Visualizer
%
% This program visualizes the process of sorting using different algorithms.

function SortingVisualizer()
    % Define the sorting algorithms to be used
    algorithms = {'Bubble Sort', 'Insertion Sort', 'Selection Sort'};
    
    % Initialize the data for visualization
    data = randi([1, 100], [10, 1]);
    y = zeros(size(data));
    
    % Create a figure with subplots
    fig = figure;
    subplot(3, 1, 1);
    plot(data);
    title('Original Data');
    xlabel('Index');
    ylabel('Value');
    
    % Visualize the sorting process for each algorithm
    for i = 1:length(algorithms)
        switch algorithms{i}
            case 'Bubble Sort'
                [data, y] = bubbleSort(data);
            case 'Insertion Sort'
                [data, y] = insertionSort(data);
            case 'Selection Sort'
                [data, y] = selectionSort(data);
        end
        
        % Update the subplot for each algorithm
        subplot(3, 1, i+1);
        plot(y);
        title([algorithms{i} ' Sorted Data']);
        xlabel('Index');
        ylabel('Value');
    end
    
    % Display the sorting visualizer
    set(fig, 'Position', [0.5, 0.5, 500, 300]);
end

function [data, y] = bubbleSort(data)
    n = length(data);
    for i = 1:n-1
        for j = 1:n-i
            if data(j) > data(j+1)
                temp = data(j);
                data(j) = data(j+1);
                data(j+1) = temp;
                y = [y, temp];
            end
        end
    end
end

function [data, y] = insertionSort(data)
    n = length(data);
    for i = 2:n
        key = data(i);
        j = i-1;
        while (j >= 1) && (data(j) > key)
            data(j+1) = data(j);
            j = j-1;
            y = [y, data(j+1)];
        end
        data(j+1) = key;
    end
end

function [data, y] = selectionSort(data)
    n = length(data);
    for i = 1:n-1
        minIndex = i;
        for j = i+1:n
            if data(j) < data(minIndex)
                minIndex = j;
            end
        end
        temp = data(i);
        data(i) = data(minIndex);
        data(minIndex) = temp;
        y = [y, temp];
    end
end