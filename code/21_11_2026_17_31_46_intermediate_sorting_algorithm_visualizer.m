% Sorting Algorithm Visualizer

function visualizer()
    % Define sorting algorithms
    sortAlgos = struct('Name', {}, 'Function', {});
    sortAlgos.Name = {'Bubble Sort', 'Insertion Sort', 'Selection Sort'};
    sortAlgos.Function = {@bubbleSort, @insertionSort, @selectionSort};

    % Initialize plot handles
    fig = figure;
    ax1 = subplot(2, 1, 1);
    ax2 = subplot(2, 1, 2);

    % Create GUI elements
    uicontrol('Style', 'text', 'String', 'Select a sorting algorithm:');
    algoCombo = uicombo('Parent', fig, 'String', sortAlgos.Name, ...
        'Value', 1);
    uicontrol('Style', 'pushbutton', 'String', 'Sort', ...
        'Callback', @(h, eventdata) sortArray(algoCombo.Value));

    % Initialize array for sorting
    array = randi([0, 100], 10, 1);

    % Plot initial array
    plot(ax1, array);
    title(ax1, 'Initial Array');
    xlabel(ax1, 'Index');
    ylabel(ax1, 'Value');

    % Sort array and update plot
    function sortArray(algo)
        sortedArray = feval(sortAlgos.Function{algo}, array);
        plot(ax2, sortedArray);
        title(ax2, ['Sorted Array (' sortAlgos.Name{algo} ')']);
        xlabel(ax2, 'Index');
        ylabel(ax2, 'Value');
    end

    % Bubble Sort
    function array = bubbleSort(array)
        n = length(array);
        for i = 1:n-1
            for j = 1:n-i
                if array(j) > array(j+1)
                    temp = array(j);
                    array(j) = array(j+1);
                    array(j+1) = temp;
                end
            end
        end
    end

    % Insertion Sort
    function array = insertionSort(array)
        n = length(array);
        for i = 2:n
            key = array(i);
            j = i-1;
            while j > 0 && array(j) > key
                array(j+1) = array(j);
                j = j-1;
            end
            array(j+1) = key;
        end
    end

    % Selection Sort
    function array = selectionSort(array)
        n = length(array);
        for i = 1:n-1
            minIndex = i;
            for j = i+1:n
                if array(j) < array(minIndex)
                    minIndex = j;
                end
            end
            temp = array(i);
            array(i) = array(minIndex);
            array(minIndex) = temp;
        end
    end

end