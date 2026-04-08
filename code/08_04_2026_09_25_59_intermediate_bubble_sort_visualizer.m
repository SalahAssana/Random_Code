% Bubble Sort Visualizer
clear; close all;

function visualizeBubbleSort()
    % Initialize data structure to hold input array
    array = randi([1 100], 10, 1);
    
    % Display initial array
    figure;
    plot(array);
    title('Initial Array');
    xlabel('Index');
    ylabel('Value');
    grid on;

    % Perform bubble sort and display intermediate steps
    for i = 2:length(array)
        swapped = false;
        for j = 1:length(array) - i + 1
            if array(j) > array(j+1)
                temp = array(j);
                array(j) = array(j+1);
                array(j+1) = temp;
                swapped = true;
            end
        end
        % Display current array
        figure;
        plot(array);
        title(['Intermediate Array after ' num2str(i-1) ' iterations']);
        xlabel('Index');
        ylabel('Value');
        grid on;
        if ~swapped
            break;
        end
    end

    % Display final sorted array
    figure;
    plot(array);
    title('Final Sorted Array');
    xlabel('Index');
    ylabel('Value');
    grid on;

end

% Call the function to start the visualization
visualizeBubbleSort();